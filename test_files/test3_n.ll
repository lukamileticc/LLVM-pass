; ModuleID = 'myModul'
source_filename = "myModul"

declare i32 @print(i32)

define i32 @x(i32 %a, i32 %b, i32 %c) {
entry:
  %c3 = alloca i32, align 4
  %b2 = alloca i32, align 4
  %a1 = alloca i32, align 4
  store i32 %a, i32* %a1, align 4
  store i32 %b, i32* %b2, align 4
  store i32 %c, i32* %c3, align 4
  %a4 = load i32, i32* %a1, align 4
  %b5 = load i32, i32* %b2, align 4
  %addtmp = add i32 %a4, %b5
  %c6 = load i32, i32* %c3, align 4
  %addtmp7 = add i32 %addtmp, %c6
  ret i32 %addtmp7
}

define i32 @begin_end_blok() {
entry:
  %c = alloca i32, align 4
  %calltmp = call i32 @x(i32 1, i32 2, i32 3)
  %calltmp1 = call i32 @x(i32 1, i32 2, i32 3)
  store i32 %calltmp1, i32* %c, align 4
  %calltmp2 = call i32 @print(i32 4)
  ret i32 %calltmp2
}
