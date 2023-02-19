################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include src/build/_deps/googletest-src/googletest/test/subdir.mk
-include src/build/_deps/googletest-src/googletest/src/subdir.mk
-include src/build/_deps/googletest-src/googletest/samples/subdir.mk
-include src/build/_deps/googletest-src/googlemock/test/subdir.mk
-include src/build/_deps/googletest-src/googlemock/src/subdir.mk
-include src/build/_deps/googletest-build/googletest/CMakeFiles/gtest_main.dir/src/subdir.mk
-include src/build/_deps/googletest-build/googletest/CMakeFiles/gtest.dir/src/subdir.mk
-include src/build/_deps/googletest-build/googlemock/CMakeFiles/gmock_main.dir/src/subdir.mk
-include src/build/_deps/googletest-build/googlemock/CMakeFiles/gmock.dir/src/subdir.mk
-include src/build/CMakeFiles/ComplexTest.dir/subdir.mk
-include src/build/CMakeFiles/3.22.1/CompilerIdCXX/subdir.mk
-include src/build/CMakeFiles/3.22.1/CompilerIdC/subdir.mk
-include src/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(CC_DEPS)),)
-include $(CC_DEPS)
endif
ifneq ($(strip $(C++_DEPS)),)
-include $(C++_DEPS)
endif
ifneq ($(strip $(C_UPPER_DEPS)),)
-include $(C_UPPER_DEPS)
endif
ifneq ($(strip $(CXX_DEPS)),)
-include $(CXX_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(CPP_DEPS)),)
-include $(CPP_DEPS)
endif
endif

-include ../makefile.defs

OPTIONAL_TOOL_DEPS := \
$(wildcard ../makefile.defs) \
$(wildcard ../makefile.init) \
$(wildcard ../makefile.targets) \


BUILD_ARTIFACT_NAME := complex
BUILD_ARTIFACT_EXTENSION :=
BUILD_ARTIFACT_PREFIX :=
BUILD_ARTIFACT := $(BUILD_ARTIFACT_PREFIX)$(BUILD_ARTIFACT_NAME)$(if $(BUILD_ARTIFACT_EXTENSION),.$(BUILD_ARTIFACT_EXTENSION),)

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all: main-build

# Main-build Target
main-build: complex

# Tool invocations
complex: $(OBJS) $(USER_OBJS) makefile objects.mk $(OPTIONAL_TOOL_DEPS)
	@echo 'Building target: $@'
	@echo 'Invoking: Cross G++ Linker'
	g++ -L/home/sescer/gt/lib -L/home/sescer/googletest/googletest/include/gtest -L/home/sescer/gt -o "complex" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(CC_DEPS)$(C++_DEPS)$(EXECUTABLES)$(OBJS)$(C_UPPER_DEPS)$(CXX_DEPS)$(C_DEPS)$(CPP_DEPS) complex
	-@echo ' '

.PHONY: all clean dependents main-build

-include ../makefile.targets
