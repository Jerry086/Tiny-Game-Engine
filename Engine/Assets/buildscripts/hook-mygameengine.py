from PyInstaller.utils.hooks import collect_data_files

# Collect files from the embedded scripts directory
datas = collect_data_files('./Assets/scripts', include_py_files=True, subdir='./Assets/scripts')

# Collect files from the definitions directory
datas += collect_data_files('./Assets/definitions', include_py_files=False, subdir='./Assets/definitions')

# Collect files from the sprites directory
datas += collect_data_files('./Assets/sprites', include_py_files=False, subdir='./Assets/sprites')

# Add more directories as needed
