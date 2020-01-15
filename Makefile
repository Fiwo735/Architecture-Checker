
checker:
	@mkdir -p bin
	@g++ src/arch_checker.cpp -o bin/arch_checker

test1: checker
	@echo "checking .aarch64 file:"
	@bin/arch_checker test/test.aarch64

test2: checker
	@echo "checking .arm file:"
	@bin/arch_checker test/test.arm

test3: checker
	@echo "checking .i386 file:"
	@bin/arch_checker test/test.i386

test4: checker
	@echo "checking .x86_64 file:"
	@bin/arch_checker test/test.x86_64

test-self: checker
	@echo "checking itself:"
	@bin/arch_checker bin/arch_checker

check-provided: checker
	@echo "checking provided file:"
	@mkdir -p test/provided
	@bin/arch_checker test/provided/*

clean:
	@rm bin/*
