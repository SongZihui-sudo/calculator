add_rules("mode.debug", "mode.release")

add_requires("loguru")

target("main")
    add_packages("loguru")
    set_kind("binary")
    add_files("./src/*.cpp")
target_end()