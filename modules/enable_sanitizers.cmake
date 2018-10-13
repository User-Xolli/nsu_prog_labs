if(ENABLE_ASAN)
	target_compile_options(${PROJECT_NAME} PUBLIC -fsanitize=address)
	target_link_libraries(${PROJECT_NAME} "C:/Program Files/LLVM/lib/clang/7.0.0/lib/windows/clang_rt.asan-x86_64.lib")
	target_compile_options(${PROJECT_NAME} PUBLIC /MT)
endif()

if(ENABLE_USAN)
	target_compile_options(${PROJECT_NAME} PUBLIC -fsanitize=undefined)
endif()
