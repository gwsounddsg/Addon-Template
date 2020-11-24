{
    "targets": [
        {
            "target_name": "myLib",
            "sources": ["myLib.cpp"],
            "include_dirs": [
                "<!(node -e \"require('nan')\")"
            ]
        }
    ]
}
