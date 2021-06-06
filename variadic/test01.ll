; ModuleID = 'test01.cpp'
source_filename = "test01.cpp"
target datalayout = "e-m:e-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

%struct.tuple_custom = type { %struct.tuple_custom.base, double }
%struct.tuple_custom.base = type <{ %struct.tuple_custom.1, i32 }>
%struct.tuple_custom.1 = type { i8* }
%struct.tuple_custom.0 = type <{ %struct.tuple_custom.1, i32, [4 x i8] }>
%struct.tuple_custom.2 = type { i8 }

$_ZN12tuple_customIJdiPKcEEC1EdiS1_ = comdat any

$_ZN12tuple_customIJdiPKcEEC2EdiS1_ = comdat any

$_ZN12tuple_customIJiPKcEEC2EiS1_ = comdat any

$_ZN12tuple_customIJPKcEEC2ES1_ = comdat any

@.str = private unnamed_addr constant [4 x i8] c"big\00", align 1

; Function Attrs: noinline norecurse nounwind optnone
define i32 @main(i32 %argc, i8** %argv) #0 {
entry:
  %retval = alloca i32, align 4
  %argc.addr = alloca i32, align 4
  %argv.addr = alloca i8**, align 8
  %t1 = alloca %struct.tuple_custom, align 8
  store i32 0, i32* %retval, align 4
  store i32 %argc, i32* %argc.addr, align 4
  store i8** %argv, i8*** %argv.addr, align 8
  call void @_ZN12tuple_customIJdiPKcEEC1EdiS1_(%struct.tuple_custom* %t1, double 1.220000e+01, i32 42, i8* getelementptr inbounds ([4 x i8], [4 x i8]* @.str, i64 0, i64 0))
  ret i32 24
}

; Function Attrs: noinline nounwind optnone
define linkonce_odr void @_ZN12tuple_customIJdiPKcEEC1EdiS1_(%struct.tuple_custom* %this, double %t, i32 %ts, i8* %ts1) unnamed_addr #1 comdat align 2 {
entry:
  %this.addr = alloca %struct.tuple_custom*, align 8
  %t.addr = alloca double, align 8
  %ts.addr = alloca i32, align 4
  %ts.addr2 = alloca i8*, align 8
  store %struct.tuple_custom* %this, %struct.tuple_custom** %this.addr, align 8
  store double %t, double* %t.addr, align 8
  store i32 %ts, i32* %ts.addr, align 4
  store i8* %ts1, i8** %ts.addr2, align 8
  %this3 = load %struct.tuple_custom*, %struct.tuple_custom** %this.addr, align 8
  %0 = load double, double* %t.addr, align 8
  %1 = load i32, i32* %ts.addr, align 4
  %2 = load i8*, i8** %ts.addr2, align 8
  call void @_ZN12tuple_customIJdiPKcEEC2EdiS1_(%struct.tuple_custom* %this3, double %0, i32 %1, i8* %2)
  ret void
}

; Function Attrs: noinline nounwind optnone
define linkonce_odr void @_ZN12tuple_customIJdiPKcEEC2EdiS1_(%struct.tuple_custom* %this, double %t, i32 %ts, i8* %ts1) unnamed_addr #1 comdat align 2 {
entry:
  %this.addr = alloca %struct.tuple_custom*, align 8
  %t.addr = alloca double, align 8
  %ts.addr = alloca i32, align 4
  %ts.addr2 = alloca i8*, align 8
  store %struct.tuple_custom* %this, %struct.tuple_custom** %this.addr, align 8
  store double %t, double* %t.addr, align 8
  store i32 %ts, i32* %ts.addr, align 4
  store i8* %ts1, i8** %ts.addr2, align 8
  %this3 = load %struct.tuple_custom*, %struct.tuple_custom** %this.addr, align 8
  %0 = bitcast %struct.tuple_custom* %this3 to %struct.tuple_custom.0*
  %1 = load i32, i32* %ts.addr, align 4
  %2 = load i8*, i8** %ts.addr2, align 8
  call void @_ZN12tuple_customIJiPKcEEC2EiS1_(%struct.tuple_custom.0* %0, i32 %1, i8* %2)
  %tail = getelementptr inbounds %struct.tuple_custom, %struct.tuple_custom* %this3, i32 0, i32 1
  %3 = load double, double* %t.addr, align 8
  store double %3, double* %tail, align 8
  ret void
}

; Function Attrs: noinline nounwind optnone
define linkonce_odr void @_ZN12tuple_customIJiPKcEEC2EiS1_(%struct.tuple_custom.0* %this, i32 %t, i8* %ts) unnamed_addr #1 comdat align 2 {
entry:
  %this.addr = alloca %struct.tuple_custom.0*, align 8
  %t.addr = alloca i32, align 4
  %ts.addr = alloca i8*, align 8
  store %struct.tuple_custom.0* %this, %struct.tuple_custom.0** %this.addr, align 8
  store i32 %t, i32* %t.addr, align 4
  store i8* %ts, i8** %ts.addr, align 8
  %this1 = load %struct.tuple_custom.0*, %struct.tuple_custom.0** %this.addr, align 8
  %0 = bitcast %struct.tuple_custom.0* %this1 to %struct.tuple_custom.1*
  %1 = load i8*, i8** %ts.addr, align 8
  call void @_ZN12tuple_customIJPKcEEC2ES1_(%struct.tuple_custom.1* %0, i8* %1)
  %tail = getelementptr inbounds %struct.tuple_custom.0, %struct.tuple_custom.0* %this1, i32 0, i32 1
  %2 = load i32, i32* %t.addr, align 4
  store i32 %2, i32* %tail, align 8
  ret void
}

; Function Attrs: noinline nounwind optnone
define linkonce_odr void @_ZN12tuple_customIJPKcEEC2ES1_(%struct.tuple_custom.1* %this, i8* %t) unnamed_addr #1 comdat align 2 {
entry:
  %this.addr = alloca %struct.tuple_custom.1*, align 8
  %t.addr = alloca i8*, align 8
  store %struct.tuple_custom.1* %this, %struct.tuple_custom.1** %this.addr, align 8
  store i8* %t, i8** %t.addr, align 8
  %this1 = load %struct.tuple_custom.1*, %struct.tuple_custom.1** %this.addr, align 8
  %0 = bitcast %struct.tuple_custom.1* %this1 to %struct.tuple_custom.2*
  %tail = getelementptr inbounds %struct.tuple_custom.1, %struct.tuple_custom.1* %this1, i32 0, i32 0
  %1 = load i8*, i8** %t.addr, align 8
  store i8* %1, i8** %tail, align 8
  ret void
}

attributes #0 = { noinline norecurse nounwind optnone "correctly-rounded-divide-sqrt-fp-math"="false" "disable-tail-calls"="false" "less-precise-fpmad"="false" "min-legal-vector-width"="0" "no-frame-pointer-elim"="false" "no-infs-fp-math"="false" "no-jump-tables"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="false" "stack-protector-buffer-size"="8" "target-features"="+cx8,+mmx,+sse,+sse2,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #1 = { noinline nounwind optnone "correctly-rounded-divide-sqrt-fp-math"="false" "disable-tail-calls"="false" "less-precise-fpmad"="false" "min-legal-vector-width"="0" "no-frame-pointer-elim"="false" "no-infs-fp-math"="false" "no-jump-tables"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="false" "stack-protector-buffer-size"="8" "target-features"="+cx8,+mmx,+sse,+sse2,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }

!llvm.module.flags = !{!0}
!llvm.ident = !{!1}

!0 = !{i32 1, !"wchar_size", i32 4}
!1 = !{!"clang version 9.0.0 (https://github.com/llvm/llvm-project/ f7e52fbdb5a7af8ea0808e98458b497125a5eca1)"}
