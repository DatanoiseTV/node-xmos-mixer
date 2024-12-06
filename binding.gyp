{
  "targets": [
    {
      "target_name": "usb_mixer",
      "sources": ["mixer_api.cpp", "usb_mixer.cpp"],
      "include_dirs": [
        "<!(node -p \"require('node-addon-api').include\")",
        "/opt/homebrew/include/libusb-1.0",
        "node_modules/node-addon-api"
      ],
      "libraries": [
        "-L/opt/homebrew/lib",
        "-lusb-1.0"
      ],
      "defines": ["NODE_ADDON_API_CPP_EXCEPTIONS"],
      "cflags": ["-std=c++17", "-fexceptions", "-stdlib=libc++", "-fPIC"],
      "cflags_cc": ["-std=c++17", "-fexceptions", "-fPIC"],
      "ldflags": ["-g"],
      'conditions': [
        ['OS=="mac"', {
          'xcode_settings': {
            'GCC_ENABLE_CPP_EXCEPTIONS': 'YES',
             "OTHER_CFLAGS": ["-g"],
             "OTHER_LDFLAGS": ["-g"]
          }
        }]
      ]
    }
  ]
}

