from PyInstaller.utils.hooks import collect_data_files

# Collect files from the embedded scripts directory
datas = collect_data_files('./scripts', include_py_files=True, subdir='./scripts')

# Collect files from the definitions directory
datas += collect_data_files('./definitions', include_py_files=False, subdir='./definitions')

# Collect files from the sprites directory
datas += collect_data_files('./sprites', include_py_files=False, subdir='./sprites')

# Add more directories as needed
