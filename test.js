const usbMixer = require('./build/Release/usb_mixer');

try {
  console.log('Testing USB Mixer addon...');
  const connectResult = usbMixer.usbMixerConnect();
  console.log('Connect result:', connectResult);
} catch (err) {
  console.error('Addon Error:', err.message);
}
