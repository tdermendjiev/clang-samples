curl http://releases.llvm.org/4.0.1/clang+llvm-4.0.1-x86_64-apple-darwin.tar.xz -o clang+llvm-4.0.1-x86_64-apple-darwin.tar.xz
tar xzf clang+llvm-4.0.1-x86_64-apple-darwin.tar.xz -C ./4.0.1
curl http://releases.llvm.org/7.0.0/clang+llvm-7.0.0-x86_64-apple-darwin.tar.xz -o clang+llvm-7.0.0-x86_64-apple-darwin.tar.xz
tar xzf clang+llvm-7.0.0-x86_64-apple-darwin.tar.xz -C ./7.0.0
patch ./4.0.1/clang+llvm-4.0.1-x86_64-apple-macosx10.9.0/include/clang/AST/RecursiveASTVisitor.h ./ast-visitor-4.0.1.patch
patch ./7.0.0/clang+llvm-7.0.0-x86_64-apple-darwin/include/clang/AST/RecursiveASTVisitor.h ./ast-visitor-7.0.0.patch
cd 4.0.1
mkdir -p cmake-build && cd cmake-build
cmake .. -GXcode
cd ../../7.0.0
mkdir -p cmake-build && cd cmake-build
cmake .. -GXcode
