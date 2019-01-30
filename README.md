**This project shows the different behavior of the Clang RecursiveASTVisitor in two versions of LLVM(4.0.1 and 7.0.0).**

The two identical XCode projects use **RecursiveASTVisitor** to walk through all declarations in the **Foundation** framework:

```
tooling::runToolOnCodeWithArgs(new MetaGenerationFrontendAction(), "#import <Foundation/Foundation.h>", clangArgs, "umbrella.h", "objc-metadata-generator");
```

While it is working as expected with **4.0.1**:

```
TranslationUnit: 20526 child declarations
```

using **7.0.0** we get:

```
TranslationUnit: 486 child declarations
```


The two patches(*ast-visitor-4.0.1.patch and ast-visitor-7.0.0.patch*)  are automatically applied in order to log the total number of declarations being visited by the tool.

**Both projects' logs are included in the repository - 4.0.1/output.log and 7.0.0/output.log.**

To generate the Xcode projects run **setup.sh**.

To clean all downloaded files and the build folders run **clean.sh**.
