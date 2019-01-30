#include <clang/Frontend/CompilerInstance.h>
#include <iostream>
#include <sstream>
#include <fstream>
#include <clang/Lex/Preprocessor.h>
#include "clang/AST/ASTConsumer.h"
#include "clang/AST/RecursiveASTVisitor.h"
#include "clang/Frontend/CompilerInstance.h"
#include "clang/Frontend/FrontendAction.h"
#include "clang/Tooling/Tooling.h"

using namespace std;
using namespace clang;

// Command line parameters
llvm::cl::opt<string> cla_clangArgumentsDelimiter(llvm::cl::Positional, llvm::cl::desc("Xclang"), llvm::cl::init("-"));
llvm::cl::list<string> cla_clangArguments(llvm::cl::ConsumeAfter, llvm::cl::desc("<clang arguments>..."));

class FindNamedClassVisitor
: public RecursiveASTVisitor<FindNamedClassVisitor> {
    public:
    explicit FindNamedClassVisitor(){}

    // this method is never called with clang 7.0.0
    bool VisitEnumDecl(EnumDecl *Declaration) {
        return true;
    }

};

class FindNamedClassConsumer : public ASTConsumer {
    public:
    explicit FindNamedClassConsumer()
    : Visitor() {}

    virtual void HandleTranslationUnit(ASTContext &Context) {
        Decl* tu = Context.getTranslationUnitDecl();
        Visitor.TraverseDecl(tu);
    }

    private:
    FindNamedClassVisitor Visitor;
};

class MetaGenerationFrontendAction : public ASTFrontendAction {
    public:
    MetaGenerationFrontendAction()
    {
    }

    virtual unique_ptr<ASTConsumer> CreateASTConsumer(CompilerInstance& Compiler, llvm::StringRef InFile) override
    {
        return unique_ptr<ASTConsumer>( new FindNamedClassConsumer());
    }
};

int main(int argc, const char** argv)
{

    llvm::cl::ParseCommandLineOptions(argc, argv);

    vector<string> clangArgs{
        "-v",
        "-x", "objective-c",
        "-fno-objc-arc", "-fmodule-maps", "-ferror-limit=0",
        "-Wno-unknown-pragmas", "-Wno-ignored-attributes", "-Wno-nullability-completeness", "-Wno-expansion-to-defined"
    };

    // merge with hardcoded clang arguments
    clangArgs.insert(clangArgs.end(), cla_clangArguments.begin(), cla_clangArguments.end());

    // Log Clang Arguments
    cout << "Clang Arguments: \n";
    for (const string& arg : clangArgs) {
        cout << "\"" << arg << "\","
        << " ";
    }
    cout << endl;

    tooling::runToolOnCodeWithArgs(new MetaGenerationFrontendAction(), "#import <Foundation/Foundation.h>", clangArgs, "umbrella.h", "objc-metadata-generator");

    return 0;
}
