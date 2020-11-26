{
    "targets": [
        {
            "target_name": "my_cpp_addon",
            "sources": ["lib/myLib.cpp"],
            "include_dirs": [
                "<!(node -e \"require('nan')\")"
            ]
        }
    ]
}
