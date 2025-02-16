import argparse
import os
import shutil
import subprocess


def clean_build():
    """Remove the build directory if it exists"""
    build_dir = "build"
    if os.path.exists(build_dir):
        print(f"Removing {build_dir} directory...")
        shutil.rmtree(build_dir)
        print("Clean completed successfully")
    else:
        print("Nothing to clean - build directory doesn't exist")


def clean_unit_tests():
    """Remove the unit-test/build directory if it exists"""
    build_dir = "unit-test/build"
    if os.path.exists(build_dir):
        print(f"Removing {build_dir} directory...")
        shutil.rmtree(build_dir)
        print("Unit-test clean completed successfully")
    else:
        print("Nothing to clean - unit-test build directory doesn't exist")


def build_project():
    """Run CMake build process"""
    build_dir = "build"

    # Create build directory if it doesn't exist
    os.makedirs(build_dir, exist_ok=True)

    # Change to build directory
    os.chdir(build_dir)

    # Run CMake commands
    try:
        print("Running CMake configuration...")
        subprocess.run(["cmake", ".."], check=True)

        print("Building project...")
        subprocess.run(["cmake", "--build", "."], check=True)

        print("Build completed successfully")
    except subprocess.CalledProcessError as e:
        print(f"Build failed with error: {e}")
        exit(1)


def build_unit_tests():
    """Run CMake build process for unit tests"""
    build_dir = "unit-test/build"

    # Create build directory if it doesn't exist
    os.makedirs(build_dir, exist_ok=True)

    # Change to build directory
    os.chdir(build_dir)

    # Run CMake commands
    try:
        print("Running CMake configuration...")
        subprocess.run(["cmake", ".."], check=True)

        print("Building unit-tests...")
        subprocess.run(["cmake", "--build", "."], check=True)

        print("Unit-tests build completed successfully")
    except subprocess.CalledProcessError as e:
        print(f"Unit-tests build failed with error: {e}")
        exit(1)


def run_clang_tidy():
    """Run clang-tidy on all C++ source files in src and inc directories"""
    cpp_files = []
    search_dirs = ["src", "inc", "unit-test"]

    # Only walk through specific directories
    for directory in search_dirs:
        if not os.path.exists(directory):
            print(f"Directory {directory} does not exist, skipping...")
            continue

        for root, dirs, files in os.walk(directory):
            # Skip the build directory in unit-test
            if "build" in dirs and directory == "unit-test":
                dirs.remove("build")

            for file in files:
                if file.endswith((".cpp", ".hpp")):
                    cpp_files.append(os.path.join(root, file))

    if not cpp_files:
        print("No C++ files found to analyze in src and inc directories")
        return

    print(f"Running clang-tidy on {len(cpp_files)} files...")
    try:
        for file in cpp_files:
            print(f"Analyzing {file}...")
            subprocess.run(["clang-tidy", file, "-p", "build"], check=True)
        print("Clang-tidy analysis completed successfully")
    except subprocess.CalledProcessError as e:
        print(f"Clang-tidy analysis failed with error: {e}")
        exit(1)


def main():
    parser = argparse.ArgumentParser(description="Build script for CMake project")
    parser.add_argument(
        "action",
        choices=["clean", "clean-unit-test", "build", "unit-test-build", "tidy"],
        help="Action to perform (clean project, clean unit-tests, build project, build unit tests or tidy)",
    )

    args = parser.parse_args()

    if args.action == "clean":
        clean_build()
    elif args.action == "clean-unit-test":
        clean_unit_tests()
    elif args.action == "build":
        build_project()
    elif args.action == "unit-test-build":
        build_unit_tests()
    elif args.action == "tidy":
        run_clang_tidy()


if __name__ == "__main__":
    main()
