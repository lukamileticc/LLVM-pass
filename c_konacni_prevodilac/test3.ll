; ModuleID = 'myModul'
source_filename = "myModul"

declare i32 @print(i32)

define i32 @x(i32 %a, i32 %b, i32 %c) {
entry:
  %c3 = alloca double
  %b2 = alloca double
  %a1 = alloca double
  store i32 %a, double* %a1
  store i32 %b, double* %b2
  store i32 %c, double* %c3
  %a4 = load double, double* %a1
  %b5 = load double, double* %b2
  %addtmp = fadd double %a4, %b5
  %c6 = load double, double* %c3
  %addtmp7 = fadd double %addtmp, %c6
  ret double %addtmp7
}

define i32 @begin_end_blok() {
entry:
  %c = alloca double
  %calltmp = call i32 @x(i32 1, i32 2, i32 3)
  %calltmp1 = call i32 @x(i32 1, i32 2, i32 3)
  store i32 %calltmp1, double* %c
  %calltmp2 = call i32 @print(i32 4)
  ret i32 %calltmp2
}
