{
    "targets": [
        {
            "target_name": "node-addon-test",
            "sources": ["myLib.cpp"],
            "include_dirs": [
                "<!(node -e \"require('nan')\")"
            ]
        }
    ]
}
