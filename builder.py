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

def run_clang_tidy():
    """Run clang-tidy on all C++ source files in src and inc directories"""
    cpp_files = []
    search_dirs = ['src', 'inc']
    
    # Only walk through specific directories
    for directory in search_dirs:
        if not os.path.exists(directory):
            print(f"Directory {directory} does not exist, skipping...")
            continue
            
        for root, _, files in os.walk(directory):
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
    parser.add_argument("action", choices=["clean", "build", "tidy"], 
                       help="Action to perform (clean, build, or tidy)")
    
    args = parser.parse_args()
    
    if args.action == "clean":
        clean_build()
    elif args.action == "build":
        build_project()
    elif args.action == "tidy":
        run_clang_tidy()

if __name__ == "__main__":
    main()