const inquirer = require('inquirer');
const path = require('path'); // Add this line to import the path module
const usbMixer = require(path.resolve(__dirname, '../build/Release/usb_mixer')); // Path resolution


async function main() {
  try {
    // Initialize USB Mixer
    const connectResult = usbMixer.usbMixerConnect();
    if (connectResult !== 0) {
      console.error('Failed to connect to USB mixer.');
      process.exit(1);
    }
    console.log('Connected to USB mixer.');

    // Display mixer info
    const numMixers = usbMixer.usbMixerGetNumMixers();
    console.log(`Number of mixers: ${numMixers}`);

    const mixerChoices = [];
    for (let i = 0; i < numMixers; i++) {
      const inputs = usbMixer.usbMixerGetNumInputs(i);
      const outputs = usbMixer.usbMixerGetNumOutputs(i);
      mixerChoices.push({ name: `Mixer ${i} (Inputs: ${inputs}, Outputs: ${outputs})`, value: i });
    }

    // Prompt user to select a mixer
    const { mixerIndex } = await inquirer.prompt([
      {
        type: 'list',
        name: 'mixerIndex',
        message: 'Select a mixer:',
        choices: mixerChoices,
      },
    ]);

    // Display mixer node values
    console.log(`Displaying mixer ${mixerIndex} nodes:`);
    displayMixerValues(mixerIndex);

    // Disconnect USB Mixer
    const disconnectResult = usbMixer.usbMixerDisconnect();
    if (disconnectResult !== 0) {
      console.error('Failed to disconnect from USB mixer.');
    } else {
      console.log('Disconnected from USB mixer.');
    }
  } catch (error) {
    console.error('Error:', error.message);
  }
}

// Display mixer values for the selected mixer
function displayMixerValues(mixerIndex) {
  const numInputs = usbMixer.usbMixerGetNumInputs(mixerIndex);
  const numOutputs = usbMixer.usbMixerGetNumOutputs(mixerIndex);

  console.log(`Inputs: ${numInputs}, Outputs: ${numOutputs}`);
  for (let input = 0; input < numInputs; input++) {
    const inputName = usbMixer.usbMixerGetInputName(mixerIndex, input);
    const values = [];
    for (let output = 0; output < numOutputs; output++) {
      const nodeValue = usbMixer.usbMixerGetValue(mixerIndex, input * numOutputs + output);
      values.push(nodeValue.toFixed(2));
    }
    console.log(`Input ${input} (${inputName}): ${values.join(', ')}`);
  }
}

main();

