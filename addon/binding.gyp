{
    "targets": [
        {
            "target_name": "myLib",
            "sources": ["lib/myLib.cpp"],
            "include_dirs": [
                "<!(node -e \"require('nan')\")"
            ]
        }
    ]
}
