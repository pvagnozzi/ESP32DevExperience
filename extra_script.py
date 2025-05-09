Import("env")
import shutil
import os
import subprocess

def before_build_spiffs(source, target, env_):
    # Copy web resources and certs to SPIFFS image folder before build
    webui_dir = os.path.join(env_["PROJECT_DIR"], "data", "webui")
    spiffs_dir = os.path.join(env_["BUILD_DIR"], "spiffs")
    certs_src = os.path.join(env_["PROJECT_DIR"], "data", "certs")
    certs_dst = os.path.join(spiffs_dir, "certs")
    if os.path.exists(spiffs_dir):
        shutil.rmtree(spiffs_dir)
    shutil.copytree(webui_dir, spiffs_dir)
    if os.path.exists(certs_src):
        shutil.copytree(certs_src, certs_dst)

def run_pytest_esp32(source, target, env_):
    build_type = env_.GetProjectOption("platformio-ide.buildType", "Release")
    if build_type == "Release":
        print("Running Python/pytest ESP32 tests before Release build...")
        result = subprocess.run(["pytest", "tests"], capture_output=True, text=True)
        print(result.stdout)
        if result.returncode != 0:
            print("Python/pytest tests failed. Aborting build.")
            exit(1)
        print("All Python/pytest tests passed.")
    # Run CMake build as part of PlatformIO build
    print("Running CMake build for src directory...")
    src_dir = os.path.join(env_["PROJECT_DIR"], "src")
    build_dir = os.path.join(src_dir, "cmake_build")
    os.makedirs(build_dir, exist_ok=True)
    cmake_cmd = ["cmake", ".."]
    build_cmd = ["cmake", "--build", "."]
    result_cmake = subprocess.run(cmake_cmd, cwd=build_dir, capture_output=True, text=True)
    print(result_cmake.stdout)
    if result_cmake.returncode != 0:
        print("CMake configuration failed. Aborting build.")
        exit(1)
    result_build = subprocess.run(build_cmd, cwd=build_dir, capture_output=True, text=True)
    print(result_build.stdout)
    if result_build.returncode != 0:
        print("CMake build failed. Aborting build.")
        exit(1)
    print("CMake build completed successfully.")

# Register the pre-build actions
env.AddPreAction("buildfs", before_build_spiffs)
env.AddPreAction("buildprog", run_pytest_esp32)
