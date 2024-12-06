#include <napi.h>
#include "usb_mixer.h" // Include the provided API header file


// Utility to throw errors
Napi::Error ThrowError(Napi::Env env, const char* message) {
    return Napi::Error::New(env, message);
}

// Wrap each API function
Napi::Number UsbMixerConnect(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();
  int result = usb_mixer_connect();
  return Napi::Number::New(env, result);
}

Napi::Number UsbMixerDisconnect(const Napi::CallbackInfo& info) {
  return Napi::Number::New(info.Env(), usb_mixer_disconnect());
}

Napi::Number UsbMixerGetNumMixers(const Napi::CallbackInfo& info) {
  return Napi::Number::New(info.Env(), usb_mixer_get_num_mixers());
}

Napi::Object UsbMixerGetLayout(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();
  unsigned int mixer = info[0].As<Napi::Number>().Uint32Value();
  unsigned int inputs, outputs;

  int result = usb_mixer_get_layout(mixer, &inputs, &outputs);
  if (result != USB_MIXER_SUCCESS) {
    throw ThrowError(env, "Failed to get mixer layout.");
  }

  Napi::Object layout = Napi::Object::New(env);
  layout.Set("inputs", Napi::Number::New(env, inputs));
  layout.Set("outputs", Napi::Number::New(env, outputs));
  return layout;
}

Napi::String UsbMixerGetInputName(const Napi::CallbackInfo& info) {
  unsigned int mixer = info[0].As<Napi::Number>().Uint32Value();
  unsigned int input = info[1].As<Napi::Number>().Uint32Value();
  return Napi::String::New(info.Env(), usb_mixer_get_input_name(mixer, input));
}

Napi::String UsbMixerGetOutputName(const Napi::CallbackInfo& info) {
  unsigned int mixer = info[0].As<Napi::Number>().Uint32Value();
  unsigned int output = info[1].As<Napi::Number>().Uint32Value();
  return Napi::String::New(info.Env(), usb_mixer_get_output_name(mixer, output));
}

Napi::Number UsbMixerGetValue(const Napi::CallbackInfo& info) {
  unsigned int mixer = info[0].As<Napi::Number>().Uint32Value();
  unsigned int mixerUnit = info[1].As<Napi::Number>().Uint32Value();
  return Napi::Number::New(info.Env(), usb_mixer_get_value(mixer, mixerUnit));
}

Napi::Number UsbMixerSetValue(const Napi::CallbackInfo& info) {
  unsigned int mixer = info[0].As<Napi::Number>().Uint32Value();
  unsigned int mixerUnit = info[1].As<Napi::Number>().Uint32Value();
  double value = info[2].As<Napi::Number>().DoubleValue();
  return Napi::Number::New(info.Env(), usb_mixer_set_value(mixer, mixerUnit, value));
}

// Add wrappers for other functions here following a similar pattern...

// Initialize module
Napi::Object Init(Napi::Env env, Napi::Object exports) {
  exports.Set("usbMixerConnect", Napi::Function::New(env, UsbMixerConnect));
  exports.Set("usbMixerDisconnect", Napi::Function::New(env, UsbMixerDisconnect));
  exports.Set("usbMixerGetNumMixers", Napi::Function::New(env, UsbMixerGetNumMixers));
  exports.Set("usbMixerGetLayout", Napi::Function::New(env, UsbMixerGetLayout));
  exports.Set("usbMixerGetInputName", Napi::Function::New(env, UsbMixerGetInputName));
  exports.Set("usbMixerGetOutputName", Napi::Function::New(env, UsbMixerGetOutputName));
  exports.Set("usbMixerGetValue", Napi::Function::New(env, UsbMixerGetValue));
  exports.Set("usbMixerSetValue", Napi::Function::New(env, UsbMixerSetValue));
  // Continue exporting other API functions...
  return exports;
}

NODE_API_MODULE(usb_mixer, Init);
