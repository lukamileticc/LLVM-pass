; ModuleID = 'myModul'
source_filename = "myModul"

define i32 @ifThenElse(i32 %a) {
entry:
  %a1 = alloca double
  store i32 %a, double* %a1
  %a2 = load double, double* %a1
  %ifcond = fcmp one double %a2, i32 0
  br i1 %ifcond, label %then, label %else

then:                                             ; preds = %entry
  store i32 100, double* %a1
  br label %ifcont

else:                                             ; preds = %entry
  store i32 0, double* %a1
  br label %ifcont

ifcont:                                           ; preds = %else, %then
  %iftmp = phi i32 [ 100, %then ], [ 0, %else ]
  ret i32 %iftmp
}
