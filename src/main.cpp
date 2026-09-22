#include "../libDaisy/src/daisy_seed.h"

using namespace daisy;

static DaisySeed hardware;

// copy each input channel straight to its output
static void AudioCallback(AudioHandle::InputBuffer in,
                          AudioHandle::OutputBuffer out,
                          size_t size) {
  for (size_t i = 0; i < size; i++) {
    out[0][i] = in[0][i];
    out[1][i] = in[1][i];
  }
}

int main() {
  hardware.Init();

  hardware.StartLog();
  // hardware.StartLog(true); // waits for connection before proceeding

  System::Delay(200);
  hardware.PrintLine("===========================================");
  hardware.PrintLine("                It's alive!                ");
  hardware.PrintLine("===========================================");
  hardware.PrintLine("");

  // audio passthru
  hardware.SetAudioBlockSize(4);
  hardware.SetAudioSampleRate(SaiHandle::Config::SampleRate::SAI_96KHZ);
  hardware.StartAudio(AudioCallback);
  hardware.PrintLine("Audio passthru running @ %d Hz, block size %d",
                     (int)hardware.AudioSampleRate(),
                     (int)hardware.AudioBlockSize());

  // blink
  while (true) {
    static bool ledState = false;
    ledState = !ledState;
    hardware.SetLed(ledState);
    System::Delay(500);
  }

  return 0;
}
