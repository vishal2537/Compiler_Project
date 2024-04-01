; ModuleID = 'input.c'
source_filename = "input.c"
target datalayout = "e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-pc-linux-gnu"

%struct.s = type { void (...)*, i32 }

; Function Attrs: noinline nounwind optnone uwtable
define dso_local void @DC() #0 {
  ret void
}

; Function Attrs: noinline nounwind optnone uwtable
define dso_local void @BC() #0 {
  call void @DC()
  ret void
}

; Function Attrs: noinline nounwind optnone uwtable
define dso_local void @F() #0 {
  ret void
}

; Function Attrs: noinline nounwind optnone uwtable
define dso_local void @E() #0 {
  ret void
}

; Function Attrs: noinline nounwind optnone uwtable
define dso_local void @D() #0 {
  ret void
}

; Function Attrs: noinline nounwind optnone uwtable
define dso_local void @C() #0 {
  call void @D()
  call void @E()
  ret void
}

; Function Attrs: noinline nounwind optnone uwtable
define dso_local void @B() #0 {
  call void @C()
  ret void
}

; Function Attrs: noinline nounwind optnone uwtable
define dso_local void @A() #0 section "Secure" {
  %1 = alloca i32, align 4
  %2 = alloca i32, align 4
  %3 = alloca i32, align 4
  store i32 10, i32* %1, align 4
  call void @B()
  ret void
}

; Function Attrs: noinline nounwind optnone uwtable
define dso_local i32 @main() #0 {
  %1 = alloca i32, align 4
  %2 = alloca void (...)*, align 8
  %3 = alloca %struct.s, align 8
  %4 = alloca void (...)*, align 8
  %5 = alloca i32, align 4
  store i32 0, i32* %1, align 4
  call void @A()
  store void (...)* bitcast (void ()* @C to void (...)*), void (...)** %2, align 8
  %6 = load void (...)*, void (...)** %2, align 8
  call void (...) %6()
  %7 = getelementptr inbounds %struct.s, %struct.s* %3, i32 0, i32 0
  store void (...)* bitcast (void ()* @F to void (...)*), void (...)** %7, align 8
  %8 = getelementptr inbounds %struct.s, %struct.s* %3, i32 0, i32 0
  %9 = load void (...)*, void (...)** %8, align 8
  call void (...) %9()
  store i32 10, i32* %5, align 4
  %10 = load i32, i32* %5, align 4
  %11 = icmp sgt i32 %10, 10
  br i1 %11, label %12, label %13

12:                                               ; preds = %0
  store void (...)* bitcast (void ()* @F to void (...)*), void (...)** %4, align 8
  br label %14

13:                                               ; preds = %0
  store void (...)* bitcast (void ()* @E to void (...)*), void (...)** %4, align 8
  br label %14

14:                                               ; preds = %13, %12
  %15 = load void (...)*, void (...)** %4, align 8
  call void (...) %15()
  %16 = load i32, i32* %1, align 4
  ret i32 %16
}

attributes #0 = { noinline nounwind optnone uwtable "frame-pointer"="all" "min-legal-vector-width"="0" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }

!llvm.module.flags = !{!0, !1, !2, !3, !4}
!llvm.ident = !{!5}

!0 = !{i32 1, !"wchar_size", i32 4}
!1 = !{i32 7, !"PIC Level", i32 2}
!2 = !{i32 7, !"PIE Level", i32 2}
!3 = !{i32 7, !"uwtable", i32 1}
!4 = !{i32 7, !"frame-pointer", i32 2}
!5 = !{!"Ubuntu clang version 14.0.0-1ubuntu1.1"}
