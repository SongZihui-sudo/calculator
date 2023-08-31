add_rules("mode.debug", "mode.release")

add_requires("loguru")

target("main")
    add_packages("loguru")
    set_kind("binary")
    add_files("./src/*.cpp")
target_end()

target("test1")
    add_packages("loguru")
    set_kind("binary")
    add_files("./test/suffix.cpp", "./src/calculator.cpp")
target_end()

target("test2")
    add_packages("loguru")
    set_kind("binary")
    add_files("./test/check_result.cpp", "./src/calculator.cpp")
target_end()