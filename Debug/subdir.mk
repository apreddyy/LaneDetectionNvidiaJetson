################################################################################

################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Binary_Frame.cpp \
../BirdView.cpp \
../GrayFrame.cpp \
../HSVFrame.cpp \
../LaneProcessing.cpp \
../Leftprocessing.cpp \
../RESIZEFrame.cpp \
../RightProcessing.cpp \
../adjust.cpp \
../processedout.cpp \
../processedout_emxAPI.cpp \
../processedout_emxutil.cpp \
../processinga.cpp \
../processingb.cpp \
../rtGetInf.cpp \
../rtGetNaN.cpp \
../rt_nonfinite.cpp \
../sobelfilter.cpp \
../unwrap.cpp 

OBJS += \
./Binary_Frame.o \
./BirdView.o \
./GrayFrame.o \
./HSVFrame.o \
./LaneProcessing.o \
./Leftprocessing.o \
./RESIZEFrame.o \
./RightProcessing.o \
./adjust.o \
./processedout.o \
./processedout_emxAPI.o \
./processedout_emxutil.o \
./processinga.o \
./processingb.o \
./rtGetInf.o \
./rtGetNaN.o \
./rt_nonfinite.o \
./sobelfilter.o \
./unwrap.o 

CPP_DEPS += \
./Binary_Frame.d \
./BirdView.d \
./GrayFrame.d \
./HSVFrame.d \
./LaneProcessing.d \
./Leftprocessing.d \
./RESIZEFrame.d \
./RightProcessing.d \
./adjust.d \
./processedout.d \
./processedout_emxAPI.d \
./processedout_emxutil.d \
./processinga.d \
./processingb.d \
./rtGetInf.d \
./rtGetNaN.d \
./rt_nonfinite.d \
./sobelfilter.d \
./unwrap.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: NVCC Compiler'
	/usr/local/cuda-9.0/bin/nvcc -I/home/pramod/cuda-workspace/LaneSystem/LaneLogic/ADVANCELANE/LaneLogic_grt_rtw -I/usr/local/cuda-9.0/include -G -g -O0 -std=c++11 -gencode arch=compute_70,code=sm_70  -odir "." -M -o "$(@:%.o=%.d)" "$<"
	/usr/local/cuda-9.0/bin/nvcc -I/home/pramod/cuda-workspace/LaneSystem/LaneLogic/ADVANCELANE/LaneLogic_grt_rtw -I/usr/local/cuda-9.0/include -G -g -O0 -std=c++11 --compile  -x c++ -o  "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


