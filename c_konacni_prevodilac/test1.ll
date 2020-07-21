; ModuleID = 'myModul'
source_filename = "myModul"

declare i32 @printd(i32)

define i32 @f1(i32 %a, i32 %b) {
entry:
  %b2 = alloca i32
  %a1 = alloca i32
  store i32 %a, i32* %a1
  store i32 %b, i32* %b2
  %a3 = load i32, i32* %a1
  %b4 = load i32, i32* %b2
  %addtmp = add i32 %a3, %b4
  %calltmp = call i32 @printd(i32 %addtmp)
  ret i32 %calltmp
}

define i32 @f2() {
entry:
  %calltmp = call i32 @printd(i32 -1)
  ret i32 %calltmp
}

define i32 @begin_end_blok() {
entry:
  %h = alloca i32
  %d = alloca i32
  %c = alloca i32
  %b = alloca i32
  %a = alloca i32
  store i32 3, i32* %a
  store i32 0, i32* %b
  store i32 0, i32* %c
  store i32 0, i32* %d
  store i32 7, i32* %h
  %a1 = load i32, i32* %a
  %b2 = load i32, i32* %b
  %calltmp = call i32 @f1(i32 %a1, i32 %b2)
  %calltmp3 = call i32 @f2()
  ret i32 %calltmp3
}
