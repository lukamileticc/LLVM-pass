; ModuleID = 'myModul'
source_filename = "myModul"

declare i32 @print(i32)

define i32 @begin_end_blok() {
entry:
  %x3 = alloca double
  %x2 = alloca double
  %x1 = alloca double
  %a = alloca double
  store i32 fadd (i32 fsub (i32 fadd (i32 fmul (i32 2, i32 4), i32 4), i32 fsub (i32 3, i32 3)), i32 2), double* %a
  %calltmp = call i32 @print(i32 4)
  %calltmp1 = call i32 @print(i32 100)
  store i32 4, double* %x1
  %x12 = load double, double* %x1
  %addtmp = fadd i32 11, double %x12
  store i32 %addtmp, double* %x2
  store i32 0, double* %x3
  %x13 = load double, double* %x1
  %calltmp4 = call i32 @print(double %x13)
  %x35 = load double, double* %x3
  %calltmp6 = call i32 @print(double %x35)
  ret i32 %calltmp6
}
