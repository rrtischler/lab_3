################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
main.obj: ../main.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C5500 Compiler'
	"C:/ti/ccsv7/tools/compiler/c5500_4.4.1/bin/cl55" -v5502 --memory_model=large -g --include_path="F:/Google Drive/UFBA/2017.2/Lab3/ccs_workspace/lab3_ativ1" --include_path="F:/Google Drive/UFBA/2017.2/Lab3/docs/PBL/lab_3/Docs/Ambientacao com o CCS/ezdsp5502_v1/C55xxCSL/include" --include_path="F:/Google Drive/UFBA/2017.2/Lab3/docs/PBL/lab_3/Docs/Ambientacao com o CCS/ezdsp5502_v1/include" --include_path="C:/ti/ccsv7/tools/compiler/c5500_4.4.1/include" --preinclude="F:/Google Drive/UFBA/2017.2/Lab3/docs/PBL/lab_3/Docs/Ambientacao com o CCS/ezdsp5502_v1/include/ezdsp5502.h" --preinclude="F:/Google Drive/UFBA/2017.2/Lab3/docs/PBL/lab_3/Docs/Ambientacao com o CCS/ezdsp5502_v1/C55xxCSL/include/csl.h" --define=c5502 --display_error_number --diag_warning=225 --ptrdiff_size=16 --preproc_with_compile --preproc_dependency="main.d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '


