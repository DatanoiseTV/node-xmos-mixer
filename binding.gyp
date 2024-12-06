{
  "targets": [
    {
      "target_name": "usb_mixer",
      "sources": ["usb_mixer.cc", "usb_mixer.cpp"],
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
      "cflags": ["-std=c++17", "-fexceptions"],
      "cflags_cc": ["-std=c++17", "-fexceptions"],
      'conditions': [
        ['OS=="mac"', {
          'xcode_settings': {
            'GCC_ENABLE_CPP_EXCEPTIONS': 'YES'
          }
        }]
      ]
    }
  ]
}

