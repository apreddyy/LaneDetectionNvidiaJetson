################################################################################

################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../LaneLogic/ADVANCELANE/LaneLogic_grt_rtw/LaneLogic.cpp \
../LaneLogic/ADVANCELANE/LaneLogic_grt_rtw/LaneLogic_capi.cpp \
../LaneLogic/ADVANCELANE/LaneLogic_grt_rtw/LaneLogic_data.cpp 

OBJS += \
./LaneLogic/ADVANCELANE/LaneLogic_grt_rtw/LaneLogic.o \
./LaneLogic/ADVANCELANE/LaneLogic_grt_rtw/LaneLogic_capi.o \
./LaneLogic/ADVANCELANE/LaneLogic_grt_rtw/LaneLogic_data.o 

CPP_DEPS += \
./LaneLogic/ADVANCELANE/LaneLogic_grt_rtw/LaneLogic.d \
./LaneLogic/ADVANCELANE/LaneLogic_grt_rtw/LaneLogic_capi.d \
./LaneLogic/ADVANCELANE/LaneLogic_grt_rtw/LaneLogic_data.d 


# Each subdirectory must supply rules for building sources it contributes
LaneLogic/ADVANCELANE/LaneLogic_grt_rtw/%.o: ../LaneLogic/ADVANCELANE/LaneLogic_grt_rtw/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: NVCC Compiler'
	/usr/local/cuda-9.0/bin/nvcc -I/home/pramod/cuda-workspace/LaneSystem/LaneLogic/ADVANCELANE/LaneLogic_grt_rtw -I/usr/local/cuda-9.0/include -G -g -O0 -std=c++11 -gencode arch=compute_70,code=sm_70  -odir "LaneLogic/ADVANCELANE/LaneLogic_grt_rtw" -M -o "$(@:%.o=%.d)" "$<"
	/usr/local/cuda-9.0/bin/nvcc -I/home/pramod/cuda-workspace/LaneSystem/LaneLogic/ADVANCELANE/LaneLogic_grt_rtw -I/usr/local/cuda-9.0/include -G -g -O0 -std=c++11 --compile  -x c++ -o  "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


