/****************************************************************************
**
** Copyright (C) 2017 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the QtQml module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:LGPL$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 3 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPL3 included in the
** packaging of this file. Please review the following information to
** ensure the GNU Lesser General Public License version 3 requirements
** will be met: https://www.gnu.org/licenses/lgpl-3.0.html.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 2.0 or (at your option) the GNU General
** Public license version 3 or any later version approved by the KDE Free
** Qt Foundation. The licenses are as published by the Free Software
** Foundation and appearing in the file LICENSE.GPL2 and LICENSE.GPL3
** included in the packaging of this file. Please review the following
** information to ensure the GNU General Public License requirements will
** be met: https://www.gnu.org/licenses/gpl-2.0.html and
** https://www.gnu.org/licenses/gpl-3.0.html.
**
** $QT_END_LICENSE$
**
****************************************************************************/
#ifndef QV4CODEGEN_P_H
#define QV4CODEGEN_P_H

//
//  W A R N I N G
//  -------------
//
// This file is not part of the Qt API.  It exists purely as an
// implementation detail.  This header file may change from version to
// version without notice, or even be removed.
//
// We mean it.
//

#include "private/qv4global_p.h"
#include <private/qqmljsastvisitor_p.h>
#include <private/qqmljsast_p.h>
#include <private/qv4compiler_p.h>
#include <private/qv4compilercontext_p.h>
#include <private/qv4util_p.h>
#include <private/qv4bytecodegenerator_p.h>
#include <private/qv4stackframe_p.h>

QT_BEGIN_NAMESPACE

using namespace QQmlJS;

namespace QV4 {

namespace Moth {
struct Instruction;
}

namespace CompiledData {
struct CompilationUnit;
}

namespace Compiler {

struct ControlFlow;
struct ControlFlowCatch;
struct ControlFlowFinally;

class Q_QML_PRIVATE_EXPORT Codegen: protected QQmlJS::AST::Visitor
{
protected:
    using BytecodeGenerator = QV4::Moth::BytecodeGenerator;
    using Instruction = QV4::Moth::Instruction;
public:
    Codegen(QV4::Compiler::JSUnitGenerator *jsUnitGenerator, bool strict);


    void generateFromProgram(const QString &fileName,
                             const QString &finalUrl,
                             const QString &sourceCode,
                             AST::Program *ast,
                             Module *module,
                             ContextType contextType = ContextType::Global);

    void generateFromModule(const QString &fileName,
                            const QString &finalUrl,
                            const QString &sourceCode,
                            AST::ESModule *ast,
                            Module *module);

public:
    class VolatileMemoryLocationScanner;
    class VolatileMemoryLocations {
        friend VolatileMemoryLocationScanner;
        bool allVolatile = false;
        QVector<QStringView> specificLocations;
    public:
        bool isVolatile(const QStringView &name) {
            if (allVolatile)
                return true;
            return specificLocations.contains(name);
        }

        void add(const QStringRef &name) { if (!allVolatile) specificLocations.append(name); }
        void setAllVolatile() { allVolatile = true; }
    };
    class RValue {
        Codegen *codegen;
        enum Type {
            Invalid,
            Accumulator,
            StackSlot,
            Const
        } type;
        union {
            Moth::StackSlot theStackSlot;
            QV4::ReturnedValue constant;
        };

    public:
        static RValue fromStackSlot(Codegen *codegen, Moth::StackSlot stackSlot) {
            RValue r;
            r.codegen = codegen;
            r.type = StackSlot;
            r.theStackSlot = stackSlot;
            return r;
        }
        static RValue fromAccumulator(Codegen *codegen) {
            RValue r;
            r.codegen = codegen;
            r.type = Accumulator;
            return r;
        }
        static RValue fromConst(Codegen *codegen, QV4::ReturnedValue value) {
            RValue r;
            r.codegen = codegen;
            r.type = Const;
            r.constant = value;
            return r;
        }

        bool operator==(const RValue &other) const;

        bool isValid() const { return type != Invalid; }
        bool isAccumulator() const { return type == Accumulator; }
        bool isStackSlot() const { return type == StackSlot; }
        bool isConst() const { return type == Const; }

        Moth::StackSlot stackSlot() const {
            Q_ASSERT(isStackSlot());
            return theStackSlot;
        }

        QV4::ReturnedValue constantValue() const {
            Q_ASSERT(isConst());
            return constant;
        }

        Q_REQUIRED_RESULT RValue storeOnStack() const;
        void loadInAccumulator() const;
    };
    struct Reference {
        enum Type {
            Invalid,
            Accumulator,
            Super,
            SuperProperty,
            StackSlot,
            ScopedLocal,
            Name,
            Member,
            Subscript,
            Import,
            QmlScopeObject,
            QmlContextObject,
            LastLValue = QmlContextObject,
            Const
        } type = Invalid;

        bool isLValue() const { return !isReadonly && type > Accumulator; }

        Reference(Codegen *cg, Type type = Invalid) : type(type), constant(0), codegen(cg) {}
        Reference(): constant(0) {}
        Reference(const Reference &) = default;
        Reference(Reference &&) = default;
        Reference &operator =(const Reference &) = default;
        Reference &operator =(Reference &&) = default;

        bool operator==(const Reference &other) const;
        bool operator!=(const Reference &other) const
        { return !(*this == other); }

        bool isValid() const { return type != Invalid; }
        bool loadTriggersSideEffect() const {
            switch (type) {
            case QmlScopeObject:
                return capturePolicy != DontCapture;
            case QmlContextObject:
                return capturePolicy != DontCapture;
            case Name:
            case Member:
            case Subscript:
            case SuperProperty:
                return true;
            default:
                return requiresTDZCheck;
            }
        }
        bool isConstant() const { return type == Const; }
        bool isAccumulator() const { return type == Accumulator; }
        bool isSuper() const { return type == Super; }
        bool isSuperProperty() const { return type == SuperProperty; }
        bool isStackSlot() const { return type == StackSlot; }
        bool isRegister() const {
            return isStackSlot();
        }

        enum PropertyCapturePolicy {
            /*
                We're reading a property from the scope or context object, but it's a CONSTANT property,
                so we don't need to register a dependency at all.
            */
            DontCapture,
            /*
                We're reading the property of a QObject, and we know that it's the
                scope object or context object, which we know very well. Instead of registering a
                property capture every time, we can do that ahead of time and then register all those
                captures in one shot in registerQmlDependencies().
            */
            CaptureAheadOfTime,
            /*
                We're reading the property of a QObject, and we're not quite sure where
                the QObject comes from or what it is. So, when reading that property at run-time,
                make sure that we capture where we read that property so that if it changes we can
                re-evaluate the entire expression.
            */
            CaptureAtRuntime
        };

        static Reference fromAccumulator(Codegen *cg) {
            return Reference(cg, Accumulator);
        }
        static Reference fromSuper(Codegen *cg) {
            return Reference(cg, Super);
        }
        static Reference fromStackSlot(Codegen *cg, int tempIndex = -1, bool isLocal = false) {
            Reference r(cg, StackSlot);
            if (tempIndex == -1)
                tempIndex = cg->bytecodeGenerator->newRegister();
            r.theStackSlot = Moth::StackSlot::createRegister(tempIndex);
            r.stackSlotIsLocalOrArgument = isLocal;
            return r;
        }
        static Reference fromArgument(Codegen *cg, int index, bool isVolatile) {
            Reference r(cg, StackSlot);
            r.theStackSlot = Moth::StackSlot::createRegister(index + sizeof(CallData)/sizeof(Value) - 1);
            r.stackSlotIsLocalOrArgument = true;
            r.isVolatile = isVolatile;
            return r;
        }
        static Reference fromScopedLocal(Codegen *cg, int index, int scope) {
            Reference r(cg, ScopedLocal);
            r.index = index;
            r.scope = scope;
            return r;
        }
        static Reference fromImport(Codegen *cg, int index) {
            Reference r(cg, Import);
            r.index = index;
            return r;
        }
        static Reference fromName(Codegen *cg, const QString &name) {
            Reference r(cg, Name);
            r.name = name;
            return r;
        }
        static Reference fromMember(const Reference &baseRef, const QString &name) {
            Reference r(baseRef.codegen, Member);
            r.propertyBase = baseRef.asRValue();
            r.propertyNameIndex = r.codegen->registerString(name);
            r.requiresTDZCheck = baseRef.requiresTDZCheck;
            return r;
        }
        static Reference fromSuperProperty(const Reference &property) {
            Q_ASSERT(property.isStackSlot());
            Reference r(property.codegen, SuperProperty);
            r.property = property.stackSlot();
            r.subscriptRequiresTDZCheck = property.requiresTDZCheck;
            return r;
        }
        static Reference fromSubscript(const Reference &baseRef, const Reference &subscript) {
            Q_ASSERT(baseRef.isStackSlot());
            Reference r(baseRef.codegen, Subscript);
            r.elementBase = baseRef.stackSlot();
            r.elementSubscript = subscript.asRValue();
            r.requiresTDZCheck = baseRef.requiresTDZCheck;
            r.subscriptRequiresTDZCheck = subscript.requiresTDZCheck;
            return r;
        }
        static Reference fromConst(Codegen *cg, QV4::ReturnedValue constant) {
            Reference r(cg, Const);
            r.constant = constant;
            r.isReadonly = true;
            return r;
        }
        static Reference fromQmlScopeObject(const Reference &base, qint16 coreIndex, qint16 notifyIndex, PropertyCapturePolicy capturePolicy) {
            Reference r(base.codegen, QmlScopeObject);
            r.qmlBase = base.storeOnStack().stackSlot();
            r.qmlCoreIndex = coreIndex;
            r.qmlNotifyIndex = notifyIndex;
            r.capturePolicy = capturePolicy;
            return r;
        }
        static Reference fromQmlContextObject(const Reference &base, qint16 coreIndex, qint16 notifyIndex, PropertyCapturePolicy capturePolicy) {
            Reference r(base.codegen, QmlContextObject);
            r.qmlBase = base.storeOnStack().stackSlot();
            r.qmlCoreIndex = coreIndex;
            r.qmlNotifyIndex = notifyIndex;
            r.capturePolicy = capturePolicy;
            return r;
        }
        static Reference fromThis(Codegen *cg) {
            Reference r = fromStackSlot(cg, CallData::This);
            r.isReadonly = true;
            // ### Optimize this. Functions that are not derived constructors or arrow functions can't have an
            // empty this object
            r.requiresTDZCheck = true;
            return r;
        }

        RValue asRValue() const;
        Reference asLValue() const;

        Q_REQUIRED_RESULT static Reference storeConstOnStack(Codegen *cg, QV4::ReturnedValue constant)
        { return Reference::fromConst(cg, constant).storeOnStack(); }

        static void storeConstOnStack(Codegen *cg, QV4::ReturnedValue constant, int stackSlot)
        { Reference::fromConst(cg, constant).storeOnStack(stackSlot); }

        Q_REQUIRED_RESULT Reference storeOnStack() const;
        void storeOnStack(int tempIndex) const;
        Q_REQUIRED_RESULT Reference storeRetainAccumulator() const;
        Reference storeConsumeAccumulator() const;

        Q_REQUIRED_RESULT Reference baseObject() const;

        bool storeWipesAccumulator() const;
        void loadInAccumulator() const;

        int nameAsIndex() const {
            Q_ASSERT(type == Name);
            return codegen->registerString(name);
        }

        Moth::StackSlot stackSlot() const {
            if (Q_UNLIKELY(!isStackSlot()))
                Q_UNREACHABLE();
            return theStackSlot;
        }

        union {
            Moth::StackSlot theStackSlot;
            QV4::ReturnedValue constant;
            struct { // Scoped arguments/Local
                int index;
                int scope;
            };
            struct {
                RValue propertyBase;
                int propertyNameIndex;
            };
            struct {
                Moth::StackSlot elementBase;
                RValue elementSubscript;
            };
            struct { // QML scope/context object case
                Moth::StackSlot qmlBase;
                qint16 qmlCoreIndex;
                qint16 qmlNotifyIndex;
                PropertyCapturePolicy capturePolicy;
            };
            Moth::StackSlot property; // super property
        };
        QString name;
        mutable bool isArgOrEval = false;
        bool isReadonly = false;
        bool isReferenceToConst = false;
        bool requiresTDZCheck = false;
        bool subscriptRequiresTDZCheck = false;
        bool stackSlotIsLocalOrArgument = false;
        bool isVolatile = false;
        bool global = false;
        Codegen *codegen = nullptr;

    private:
        void storeAccumulator() const;
        Reference doStoreOnStack(int tempIndex) const;
    };

    struct RegisterScope {
        RegisterScope(Codegen *cg)
            : generator(cg->bytecodeGenerator),
              regCountForScope(generator->currentReg) {}
        ~RegisterScope() {
            generator->currentReg = regCountForScope;
        }
        BytecodeGenerator *generator;
        int regCountForScope;
    };

    struct ObjectPropertyValue {
        ObjectPropertyValue() {}

        Reference rvalue;
        int getter = -1; // index in _module->functions or -1 if not set
        int setter = -1;
        uint keyAsIndex = UINT_MAX;

        bool hasGetter() const { return getter >= 0; }
        bool hasSetter() const { return setter >= 0; }
    };
protected:

    enum Format { ex, cx, nx };
    class Result {
        Reference _result;

        const BytecodeGenerator::Label *_iftrue = nullptr;
        const BytecodeGenerator::Label *_iffalse = nullptr;
        Format _format = ex;
        Format _requested;
        bool _trueBlockFollowsCondition = false;

    public:
        explicit Result(const Reference &lrvalue)
            : _result(lrvalue)
            , _requested(ex)
        {}

        explicit Result(Format requested = ex)
            : _requested(requested) {}

        explicit Result(const BytecodeGenerator::Label *iftrue,
                        const BytecodeGenerator::Label *iffalse,
                        bool trueBlockFollowsCondition)
            : _iftrue(iftrue)
            , _iffalse(iffalse)
            , _requested(cx)
            , _trueBlockFollowsCondition(trueBlockFollowsCondition)
        {
            Q_ASSERT(iftrue);
            Q_ASSERT(iffalse);
        }

        const BytecodeGenerator::Label *iftrue() const {
            Q_ASSERT(_requested == cx);
            return _iftrue;
        }

        const BytecodeGenerator::Label *iffalse() const {
            Q_ASSERT(_requested == cx);
            return _iffalse;
        }

        Format format() const {
            return _format;
        }

        bool accept(Format f)
        {
            if (_requested == f) {
                _format = f;
                return true;
            }
            return false;
        }

        bool trueBlockFollowsCondition() const {
            return _trueBlockFollowsCondition;
        }

        const Reference &result() const {
            return _result;
        }

        void setResult(const Reference &result) {
            _result = result;
        }
    };

    void enterContext(AST::Node *node);
    int leaveContext();
public:
    Context *enterBlock(AST::Node *node);
    int leaveBlock() { return leaveContext(); }
protected:
    void leaveLoop();

    enum UnaryOperation {
        UPlus,
        UMinus,
        PreIncrement,
        PreDecrement,
        PostIncrement,
        PostDecrement,
        Not,
        Compl
    };

    Reference unop(UnaryOperation op, const Reference &expr);

    void addCJump();

public:
    int registerString(const QString &name) {
        return jsUnitGenerator->registerString(name);
    }
    int registerConstant(QV4::ReturnedValue v) { return jsUnitGenerator->registerConstant(v); }
    int registerGetterLookup(int nameIndex) { return jsUnitGenerator->registerGetterLookup(nameIndex); }
    int registerSetterLookup(int nameIndex) { return jsUnitGenerator->registerSetterLookup(nameIndex); }
    int registerGlobalGetterLookup(int nameIndex) { return jsUnitGenerator->registerGlobalGetterLookup(nameIndex); }

    // Returns index in _module->functions
    virtual int defineFunction(const QString &name, AST::Node *ast,
                               AST::FormalParameterList *formals,
                               AST::StatementList *body);

protected:
    void statement(AST::Statement *ast);
    void statement(AST::ExpressionNode *ast);
    void condition(AST::ExpressionNode *ast, const BytecodeGenerator::Label *iftrue,
                   const BytecodeGenerator::Label *iffalse,
                   bool trueBlockFollowsCondition);
    Reference expression(AST::ExpressionNode *ast);

    void accept(AST::Node *node);

    void program(AST::Program *ast);
    void statementList(AST::StatementList *ast);
    void variableDeclaration(AST::PatternElement *ast);
    void variableDeclarationList(AST::VariableDeclarationList *ast);

    Reference targetForPatternElement(AST::PatternElement *p);
    void initializeAndDestructureBindingElement(AST::PatternElement *e, const Reference &baseRef = Reference(), bool isDefinition = false);
    void destructurePropertyList(const Reference &object, AST::PatternPropertyList *bindingList, bool isDefinition = false);
    void destructureElementList(const Reference &array, AST::PatternElementList *bindingList, bool isDefinition = false);
    void destructurePattern(AST::Pattern *p, const Reference &rhs);

    Reference referenceForPropertyName(const Codegen::Reference &object, AST::PropertyName *name);

    // Hook provided to implement QML lookup semantics
    virtual Reference fallbackNameLookup(const QString &name);
    virtual void beginFunctionBodyHook() {}

    void emitReturn(const Reference &expr);

    // nodes
    bool visit(AST::ArgumentList *ast) override;
    bool visit(AST::CaseBlock *ast) override;
    bool visit(AST::CaseClause *ast) override;
    bool visit(AST::CaseClauses *ast) override;
    bool visit(AST::Catch *ast) override;
    bool visit(AST::DefaultClause *ast) override;
    bool visit(AST::Elision *ast) override;
    bool visit(AST::Finally *ast) override;
    bool visit(AST::FormalParameterList *ast) override;
    bool visit(AST::Program *ast) override;
    bool visit(AST::StatementList *ast) override;
    bool visit(AST::UiArrayMemberList *ast) override;
    bool visit(AST::UiImport *ast) override;
    bool visit(AST::UiHeaderItemList *ast) override;
    bool visit(AST::UiPragma *ast) override;
    bool visit(AST::UiObjectInitializer *ast) override;
    bool visit(AST::UiObjectMemberList *ast) override;
    bool visit(AST::UiParameterList *ast) override;
    bool visit(AST::UiProgram *ast) override;
    bool visit(AST::UiQualifiedId *ast) override;
    bool visit(AST::VariableDeclarationList *ast) override;

    bool visit(AST::PatternElement *ast) override;
    bool visit(AST::PatternElementList *ast) override;
    bool visit(AST::PatternProperty *ast) override;
    bool visit(AST::PatternPropertyList *ast) override;

    bool visit(AST::ExportDeclaration *ast) override;

    // expressions
    bool visit(AST::Expression *ast) override;
    bool visit(AST::ArrayPattern *ast) override;
    bool visit(AST::ArrayMemberExpression *ast) override;
    bool visit(AST::BinaryExpression *ast) override;
    bool visit(AST::CallExpression *ast) override;
    bool visit(AST::ConditionalExpression *ast) override;
    bool visit(AST::DeleteExpression *ast) override;
    bool visit(AST::FalseLiteral *ast) override;
    bool visit(AST::SuperLiteral *ast) override;
    bool visit(AST::FieldMemberExpression *ast) override;
    bool visit(AST::TaggedTemplate *ast) override;
    bool visit(AST::FunctionExpression *ast) override;
    bool visit(AST::IdentifierExpression *ast) override;
    bool visit(AST::NestedExpression *ast) override;
    bool visit(AST::NewExpression *ast) override;
    bool visit(AST::NewMemberExpression *ast) override;
    bool visit(AST::NotExpression *ast) override;
    bool visit(AST::NullExpression *ast) override;
    bool visit(AST::NumericLiteral *ast) override;
    bool visit(AST::ObjectPattern *ast) override;
    bool visit(AST::PostDecrementExpression *ast) override;
    bool visit(AST::PostIncrementExpression *ast) override;
    bool visit(AST::PreDecrementExpression *ast) override;
    bool visit(AST::PreIncrementExpression *ast) override;
    bool visit(AST::RegExpLiteral *ast) override;
    bool visit(AST::StringLiteral *ast) override;
    bool visit(AST::TemplateLiteral *ast) override;
    bool visit(AST::ThisExpression *ast) override;
    bool visit(AST::TildeExpression *ast) override;
    bool visit(AST::TrueLiteral *ast) override;
    bool visit(AST::TypeOfExpression *ast) override;
    bool visit(AST::UnaryMinusExpression *ast) override;
    bool visit(AST::UnaryPlusExpression *ast) override;
    bool visit(AST::VoidExpression *ast) override;
    bool visit(AST::FunctionDeclaration *ast) override;
    bool visit(AST::YieldExpression *ast) override;
    bool visit(AST::ClassExpression *ast) override;
    bool visit(AST::ClassDeclaration *ast) override;

    // statements
    bool visit(AST::Block *ast) override;
    bool visit(AST::BreakStatement *ast) override;
    bool visit(AST::ContinueStatement *ast) override;
    bool visit(AST::DebuggerStatement *ast) override;
    bool visit(AST::DoWhileStatement *ast) override;
    bool visit(AST::EmptyStatement *ast) override;
    bool visit(AST::ExpressionStatement *ast) override;
    bool visit(AST::ForEachStatement *ast) override;
    bool visit(AST::ForStatement *ast) override;
    bool visit(AST::IfStatement *ast) override;
    bool visit(AST::LabelledStatement *ast) override;
    bool visit(AST::ReturnStatement *ast) override;
    bool visit(AST::SwitchStatement *ast) override;
    bool visit(AST::ThrowStatement *ast) override;
    bool visit(AST::TryStatement *ast) override;
    bool visit(AST::VariableStatement *ast) override;
    bool visit(AST::WhileStatement *ast) override;
    bool visit(AST::WithStatement *ast) override;

    // ui object members
    bool visit(AST::UiArrayBinding *ast) override;
    bool visit(AST::UiObjectBinding *ast) override;
    bool visit(AST::UiObjectDefinition *ast) override;
    bool visit(AST::UiPublicMember *ast) override;
    bool visit(AST::UiScriptBinding *ast) override;
    bool visit(AST::UiSourceElement *ast) override;

    bool throwSyntaxErrorOnEvalOrArgumentsInStrictMode(const Reference &r, const AST::SourceLocation &loc);
    virtual void throwSyntaxError(const AST::SourceLocation &loc, const QString &detail);
    virtual void throwReferenceError(const AST::SourceLocation &loc, const QString &detail);

public:
    QList<DiagnosticMessage> errors() const;
#ifndef V4_BOOTSTRAP
    QList<QQmlError> qmlErrors() const;
#endif

    Reference binopHelper(QSOperator::Op oper, Reference &left, Reference &right);
    Reference jumpBinop(QSOperator::Op oper, Reference &left, Reference &right);
    struct Arguments { int argc; int argv; bool hasSpread; };
    Arguments pushArgs(AST::ArgumentList *args);
    void handleCall(Reference &base, Arguments calldata, int slotForFunction, int slotForThisObject);

    Arguments pushTemplateArgs(AST::TemplateLiteral *args);
    void createTemplateObject(AST::TemplateLiteral *t);

    void setUseFastLookups(bool b) { useFastLookups = b; }

    void handleTryCatch(AST::TryStatement *ast);
    void handleTryFinally(AST::TryStatement *ast);


    Reference referenceForName(const QString &name, bool lhs, const QQmlJS::AST::SourceLocation &accessLocation = QQmlJS::AST::SourceLocation());

    QQmlRefPointer<QV4::CompiledData::CompilationUnit> generateCompilationUnit(bool generateUnitData = true);
    static QQmlRefPointer<QV4::CompiledData::CompilationUnit> createUnitForLoading();

    Context *currentContext() const { return _context; }
    BytecodeGenerator *generator() const { return bytecodeGenerator; }

    void loadClosure(int index);

    Module *module() const { return _module; }

    BytecodeGenerator::Label returnLabel() {
        if (!_returnLabel)
            _returnLabel = new BytecodeGenerator::Label(bytecodeGenerator->newLabel());
        return *_returnLabel;
    }

    void setGlobalNames(const QSet<QString>& globalNames) {
        m_globalNames = globalNames;
    }


protected:
    friend class ScanFunctions;
    friend struct ControlFlow;
    friend struct ControlFlowCatch;
    friend struct ControlFlowFinally;
    Result _expr;
    VolatileMemoryLocations _volatileMemoryLocations;
    Module *_module;
    int _returnAddress;
    Context *_context;
    Context *_functionContext = nullptr;
    AST::LabelledStatement *_labelledStatement;
    QV4::Compiler::JSUnitGenerator *jsUnitGenerator;
    BytecodeGenerator *bytecodeGenerator = nullptr;
    Moth::BytecodeGenerator::Label *_returnLabel = nullptr;
    bool _strictMode;
    bool useFastLookups = true;
    bool requiresReturnValue = false;
    bool insideSwitch = false;
    bool inFormalParameterList = false;
    bool functionEndsWithReturn = false;
    bool _tailCallsAreAllowed = true;
    QSet<QString> m_globalNames;

    ControlFlow *controlFlow = nullptr;

    bool _fileNameIsUrl;
    bool hasError;
    QList<QQmlJS::DiagnosticMessage> _errors;

    class TailCallBlocker
    {
    public:
        TailCallBlocker(Codegen *cg, bool onoff = false)
            : _cg(cg)
            , _saved(_cg->_tailCallsAreAllowed)
            , _onoff(onoff)
        { _cg->_tailCallsAreAllowed = onoff; }

        ~TailCallBlocker()
        { _cg->_tailCallsAreAllowed = _saved; }

        void unblock() const
        { _cg->_tailCallsAreAllowed = _saved; }

        void reblock() const
        { _cg->_tailCallsAreAllowed = _onoff; }

    private:
        Codegen *_cg;
        bool _saved;
        bool _onoff;
    };

    class RecursionDepthCheck {
    public:
        RecursionDepthCheck(Codegen *cg, const AST::SourceLocation &loc)
            : _cg(cg)
        {
#ifdef QT_NO_DEBUG
            const int depthLimit = 4000; // limit to ~1000 deep
#else
            const int depthLimit = 1000; // limit to ~250 deep
#endif // QT_NO_DEBUG

            ++_cg->_recursionDepth;
            if (_cg->_recursionDepth > depthLimit)
                _cg->throwSyntaxError(loc, QStringLiteral("Maximum statement or expression depth exceeded"));
        }

        ~RecursionDepthCheck()
        { --_cg->_recursionDepth; }

    private:
        Codegen *_cg;
    };
    int _recursionDepth = 0;
    friend class RecursionDepthCheck;

private:
    VolatileMemoryLocations scanVolatileMemoryLocations(AST::Node *ast) const;
    void handleConstruct(const Reference &base, AST::ArgumentList *args);
};

}

}

QT_END_NAMESPACE

#endif // QV4CODEGEN_P_H
