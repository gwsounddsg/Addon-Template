{
    "targets": [
        {
            "target_name": "node-addon-test",
            "sources": ["lib/my-lib.cpp"],
            "include_dirs": [
                "<!(node -e \"require('nan')\")"
            ]
        }
    ]
}
