*Prerequiste
1. download ninja & gn for your platform and setting proper search path for execute ninja and gn.
   ninja : https://github.com/ninja-build/ninja/releases  
   gn linux : https://chrome-infra-packages.appspot.com/dl/gn/gn/linux-amd64/+/latest
   gn macOS : https://chrome-infra-packages.appspot.com/dl/gn/gn/mac-amd64/+/latest
   gn Windows : https://chrome-infra-packages.appspot.com/dl/gn/gn/windows-amd64/+/latest

2. download source code e.g. git clone https://github.com/fantasialin/cpp_sandbox.git


*build steps

1. cd cpp_sandbox
2. gn gen out
3. ninja -C out

