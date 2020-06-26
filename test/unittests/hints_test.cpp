#include "hints.h"

#include <catch.hpp>

using namespace centurion;
using namespace hint;

namespace {

template <typename Hint, typename Lambda>
void test_hint(Lambda&& lambda)
{
  const auto optPrev = get_hint<Hint>();

  lambda();

  if (optPrev) {
    set_hint<Hint, Prio::Default>(*optPrev);
  }
}

template <typename Hint>
void test_bool_hint()
{
  test_hint<Hint>([] {
    CHECK(set_hint<Hint>(true));
    CHECK(get_hint<Hint>().value());

    CHECK(set_hint<Hint>(false));
    CHECK(!get_hint<Hint>().value());
  });
}

}  // namespace

TEST_CASE("HintPrio", "[Hints]")
{
  CHECK(Prio::Default == static_cast<Prio>(SDL_HINT_DEFAULT));
  CHECK(Prio::Normal == static_cast<Prio>(SDL_HINT_NORMAL));
  CHECK(Prio::Override == static_cast<Prio>(SDL_HINT_OVERRIDE));

  CHECK(static_cast<Prio>(SDL_HINT_DEFAULT) == Prio::Default);
  CHECK(static_cast<Prio>(SDL_HINT_NORMAL) == Prio::Normal);
  CHECK(static_cast<Prio>(SDL_HINT_OVERRIDE) == Prio::Override);
}

TEST_CASE("set_hint", "[Hints]")
{
  SECTION("AccelerometerAsJoystick")
  {
    test_bool_hint<AccelerometerAsJoystick>();
  }

  SECTION("AllowTopMost") { test_bool_hint<AllowTopMost>(); }

  SECTION("AudioResamplingMode")
  {
    using Event = AudioResamplingMode;
    test_hint<Event>([] {
      set_hint<Event>(Event::Default);
      CHECK(get_hint<Event>().value() == Event::Default);

      set_hint<Event>(Event::Fast);
      CHECK(get_hint<Event>().value() == Event::Fast);

      set_hint<Event>(Event::Medium);
      CHECK(get_hint<Event>().value() == Event::Medium);

      set_hint<Event>(Event::Best);
      CHECK(get_hint<Event>().value() == Event::Best);
    });
  }

  SECTION("AndroidBlockOnPause") { test_bool_hint<AndroidBlockOnPause>(); }

  SECTION("AndroidTrapBackButton") { test_bool_hint<AndroidTrapBackButton>(); }

  SECTION("AndroidAPKExpansionMainFileVersion")
  {
    using AndroidMainFile = AndroidAPKExpansionMainFileVersion;
    test_hint<AndroidMainFile>([] {
      CHECK(set_hint<AndroidMainFile>(1));
      CHECK(get_hint<AndroidMainFile>() == 1);
    });
  }

  SECTION("AndroidAPKExpansionPatchFileVersion")
  {
    using AndroidPatchFile = AndroidAPKExpansionPatchFileVersion;
    test_hint<AndroidPatchFile>([] {
      CHECK(set_hint<AndroidPatchFile>(1));
      CHECK(get_hint<AndroidPatchFile>() == 1);
    });
  }

  SECTION("AudioCategory")
  {
    test_hint<AudioCategory>([] {
      CHECK(set_hint<AudioCategory>(AudioCategory::Ambient));
      CHECK(get_hint<AudioCategory>() == AudioCategory::Ambient);

      CHECK(set_hint<AudioCategory>(AudioCategory::Playback));
      CHECK(get_hint<AudioCategory>() == AudioCategory::Playback);
    });
  }

  SECTION("AppleTVControllerUIEvents")
  {
    test_bool_hint<AppleTVControllerUIEvents>();
  }

  SECTION("AppleTVRemoteAllowRotation")
  {
    test_bool_hint<AppleTVRemoteAllowRotation>();
  }

  SECTION("BMPSaveLegacyFormat") { test_bool_hint<BMPSaveLegacyFormat>(); }

  SECTION("DoubleBuffer") { test_bool_hint<DoubleBuffer>(); }

  SECTION("DisplayUsableBounds")
  {
    test_hint<DisplayUsableBounds>([] {
      const CZString str = "10, 20, 30, 40";
      CHECK(set_hint<DisplayUsableBounds>(str));
      CHECK_THAT(get_hint<DisplayUsableBounds>().value(), Catch::Equals(str));
    });
  }

  SECTION("EmscriptenKeyboardElement")
  {
    using Hint = EmscriptenKeyboardElement;
    test_hint<Hint>([] {
      CHECK(set_hint<Hint>("#window"));
      CHECK_THAT(get_hint<Hint>().value(), Catch::Equals("#window"));

      CHECK(set_hint<Hint>("#document"));
      CHECK_THAT(get_hint<Hint>().value(), Catch::Equals("#document"));

      CHECK(set_hint<Hint>("#screen"));
      CHECK_THAT(get_hint<Hint>().value(), Catch::Equals("#screen"));

      CHECK(set_hint<Hint>("#canvas"));
      CHECK_THAT(get_hint<Hint>().value(), Catch::Equals("#canvas"));
    });
  }

  SECTION("EnableSteamControllers")
  {
    test_bool_hint<EnableSteamControllers>();
  }

  SECTION("EventLogging")
  {
    test_hint<EventLogging>([] {
      set_hint<EventLogging>(0);
      CHECK(get_hint<EventLogging>().value() == 0);

      set_hint<EventLogging>(1);
      CHECK(get_hint<EventLogging>().value() == 1);

      set_hint<EventLogging>(2);
      CHECK(get_hint<EventLogging>().value() == 2);
    });

    set_hint<EventLogging>(0);
  }

  SECTION("FramebufferAcceleration")
  {
    using Hint = FramebufferAcceleration;
    test_hint<Hint>([] {
      set_hint<Hint>(Hint::Off);
      CHECK(get_hint<Hint>().value() == Hint::Off);

      set_hint<Hint>(Hint::On);
      CHECK(get_hint<Hint>().value() == Hint::On);

      set_hint<Hint>(Hint::OpenGL);
      CHECK(get_hint<Hint>().value() == Hint::OpenGL);

      set_hint<Hint>(Hint::OpenGLES);
      CHECK(get_hint<Hint>().value() == Hint::OpenGLES);

      set_hint<Hint>(Hint::OpenGLES2);
      CHECK(get_hint<Hint>().value() == Hint::OpenGLES2);

      set_hint<Hint>(Hint::Direct3D);
      CHECK(get_hint<Hint>().value() == Hint::Direct3D);

      set_hint<Hint>(Hint::Metal);
      CHECK(get_hint<Hint>().value() == Hint::Metal);

      set_hint<Hint>(Hint::Software);
      CHECK(get_hint<Hint>().value() == Hint::Software);
    });
  }

  SECTION("GameControllerUseButtonLabels")
  {
    test_bool_hint<GameControllerUseButtonLabels>();
  }

  SECTION("GameControllerType")
  {
    test_hint<GameControllerType>([] {
      const CZString str = "0x00FD/0xAAC3=PS4";
      set_hint<GameControllerType>(str);
      CHECK_THAT(get_hint<GameControllerType>().value(), Catch::Equals(str));
    });
  }

  SECTION("GameControllerConfig")
  {
    test_hint<GameControllerConfig>([] {
      const CZString str = "asd\nasd";
      set_hint<GameControllerConfig>(str);
      CHECK_THAT(get_hint<GameControllerConfig>().value(), Catch::Equals(str));
    });
  }

  SECTION("GameControllerConfigFile")
  {
    test_hint<GameControllerConfigFile>([] {
      const CZString str = "foo";
      set_hint<GameControllerConfigFile>(str);
      CHECK_THAT(get_hint<GameControllerConfigFile>().value(),
                 Catch::Equals(str));
    });
  }

  SECTION("GameControllerIgnoreDevices")
  {
    test_hint<GameControllerIgnoreDevices>([] {
      const CZString str = "0xAAAA/0xBBBB, 0xCCCC/0xDDDD";
      set_hint<GameControllerIgnoreDevices>(str);
      CHECK_THAT(get_hint<GameControllerIgnoreDevices>().value(),
                 Catch::Equals(str));
    });
  }

  SECTION("GameControllerIgnoreDevicesExcept")
  {
    test_hint<GameControllerIgnoreDevicesExcept>([] {
      const CZString str = "0xAAAA/0xBBBB, 0xCCCC/0xDDDD";
      set_hint<GameControllerIgnoreDevicesExcept>(str);
      CHECK_THAT(get_hint<GameControllerIgnoreDevicesExcept>().value(),
                 Catch::Equals(str));
    });
  }

  SECTION("GrabKeyboard") { test_bool_hint<GrabKeyboard>(); }

  SECTION("FramebufferAcceleration")
  {
    //    test_bool_hint<FramebufferAcceleration>();
  }

  SECTION("IdleTimerDisabled") { test_bool_hint<IdleTimerDisabled>(); }

  SECTION("IMEInternalEditing") { test_bool_hint<IMEInternalEditing>(); }

  SECTION("JoystickAllowBackgroundEvents")
  {
    test_bool_hint<JoystickAllowBackgroundEvents>();
  }

  SECTION("JoystickUseHIDAPI") { test_bool_hint<JoystickUseHIDAPI>(); }

  SECTION("JoystickUseHIDAPIPS4") { test_bool_hint<JoystickUseHIDAPIPS4>(); }

  SECTION("JoystickUseHIDAPISteam")
  {
    test_bool_hint<JoystickUseHIDAPISteam>();
  }

  SECTION("JoystickUseHIDAPISwitch")
  {
    test_bool_hint<JoystickUseHIDAPISwitch>();
  }

  SECTION("JoystickUseHIDAPIXbox") { test_bool_hint<JoystickUseHIDAPIXbox>(); }

  SECTION("JoystickUseHIDAPIGameCube")
  {
    test_bool_hint<JoystickUseHIDAPIGameCube>();
  }

  SECTION("LogicalSizeMode")
  {
    test_hint<LogicalSizeMode>([] {
      CHECK(set_hint<LogicalSizeMode>(LogicalSizeMode::Letterbox));
      CHECK(get_hint<LogicalSizeMode>().value() == LogicalSizeMode::Letterbox);

      CHECK(set_hint<LogicalSizeMode>(LogicalSizeMode::Overscan));
      CHECK(get_hint<LogicalSizeMode>().value() == LogicalSizeMode::Overscan);
    });
  }

  SECTION("MacBackgroundApp") { test_bool_hint<MacBackgroundApp>(); }

  SECTION("MacCTRLClickEmulateRightClick")
  {
    test_bool_hint<MacCTRLClickEmulateRightClick>();
  }

  SECTION("MouseFocusClickthrough")
  {
    test_bool_hint<MouseFocusClickthrough>();
  }

  SECTION("MouseRelativeModeWarp") { test_bool_hint<MouseRelativeModeWarp>(); }

  SECTION("MouseDoubleClickRadius")
  {
    test_hint<MouseDoubleClickRadius>([] {
      set_hint<MouseDoubleClickRadius>(5);
      CHECK(get_hint<MouseDoubleClickRadius>().value() == 5);

      set_hint<MouseDoubleClickRadius>(20);
      CHECK(get_hint<MouseDoubleClickRadius>().value() == 20);
    });
  }

  SECTION("MouseDoubleClickTime")
  {
    test_hint<MouseDoubleClickTime>([] {
      set_hint<MouseDoubleClickTime>(25);
      CHECK(get_hint<MouseDoubleClickTime>().value() == 25);

      set_hint<MouseDoubleClickTime>(178);
      CHECK(get_hint<MouseDoubleClickTime>().value() == 178);
    });
  }

  SECTION("NoSignalHandlers") { test_bool_hint<NoSignalHandlers>(); };

  SECTION("Direct3D11Debug") { test_bool_hint<Direct3D11Debug>(); };

  SECTION("Direct3DThreadSafe") { test_bool_hint<Direct3DThreadSafe>(); };

  SECTION("EnableOpenGLShaders") { test_bool_hint<EnableOpenGLShaders>(); };

  SECTION("OpenGLESDriver") { test_bool_hint<OpenGLESDriver>(); };

  SECTION("EnableVSync")
  {
    test_bool_hint<EnableVSync>();
    set_hint<EnableVSync>(true);

    //    SDL_SetHint(SDL_HINT_RENDER_VSYNC, nullptr);
  };

  SECTION("ScaleQuality")
  {
    test_hint<ScaleQuality>([] {
      set_hint<ScaleQuality>(ScaleQuality::Nearest);
      CHECK(get_hint<ScaleQuality>() == ScaleQuality::Nearest);

      set_hint<ScaleQuality>(ScaleQuality::Linear);
      CHECK(get_hint<ScaleQuality>() == ScaleQuality::Linear);

      set_hint<ScaleQuality>(ScaleQuality::Best);
      CHECK(get_hint<ScaleQuality>() == ScaleQuality::Best);
    });
  };

  SECTION("AllowScreensaver") { test_bool_hint<AllowScreensaver>(); };

  SECTION("VideoExternalContext") { test_bool_hint<VideoExternalContext>(); };

  SECTION("DisableHighDPI") { test_bool_hint<DisableHighDPI>(); };

  SECTION("MacFullscreenSpaces") { test_bool_hint<MacFullscreenSpaces>(); };

  SECTION("MinimizeOnFocusLoss") { test_bool_hint<MinimizeOnFocusLoss>(); };

  SECTION("X11NetWMPing") { test_bool_hint<X11NetWMPing>(); };

  SECTION("X11XNetWMBypassCompositor")
  {
    test_bool_hint<X11XNetWMBypassCompositor>();
  };

  SECTION("X11ForceEGL") { test_bool_hint<X11ForceEGL>(); };

  SECTION("X11Xinerama") { test_bool_hint<X11Xinerama>(); };

  SECTION("X11XRandR") { test_bool_hint<X11XRandR>(); };

  SECTION("X11XVidMode") { test_bool_hint<X11XVidMode>(); };

  SECTION("WAVERIFFChunkSize")
  {
    test_hint<WAVERIFFChunkSize>([] {
      CHECK(set_hint<WAVERIFFChunkSize>(WAVERIFFChunkSize::Force));
      CHECK(get_hint<WAVERIFFChunkSize>() == WAVERIFFChunkSize::Force);

      CHECK(set_hint<WAVERIFFChunkSize>(WAVERIFFChunkSize::IgnoreZero));
      CHECK(get_hint<WAVERIFFChunkSize>() == WAVERIFFChunkSize::IgnoreZero);

      CHECK(set_hint<WAVERIFFChunkSize>(WAVERIFFChunkSize::Ignore));
      CHECK(get_hint<WAVERIFFChunkSize>() == WAVERIFFChunkSize::Ignore);

      CHECK(set_hint<WAVERIFFChunkSize>(WAVERIFFChunkSize::Maximum));
      CHECK(get_hint<WAVERIFFChunkSize>() == WAVERIFFChunkSize::Maximum);
    });
  };

  SECTION("WAVETruncation")
  {
    test_hint<WAVETruncation>([] {
      CHECK(set_hint<WAVETruncation>(WAVETruncation::VeryStrict));
      CHECK(get_hint<WAVETruncation>() == WAVETruncation::VeryStrict);

      CHECK(set_hint<WAVETruncation>(WAVETruncation::Strict));
      CHECK(get_hint<WAVETruncation>() == WAVETruncation::Strict);

      CHECK(set_hint<WAVETruncation>(WAVETruncation::DropFrame));
      CHECK(get_hint<WAVETruncation>() == WAVETruncation::DropFrame);

      CHECK(set_hint<WAVETruncation>(WAVETruncation::DropBlock));
      CHECK(get_hint<WAVETruncation>() == WAVETruncation::DropBlock);
    });
  };

  SECTION("WAVEFactChunk")
  {
    test_hint<WAVEFactChunk>([] {
      CHECK(set_hint<WAVEFactChunk>(WAVEFactChunk::Truncate));
      CHECK(get_hint<WAVEFactChunk>() == WAVEFactChunk::Truncate);

      CHECK(set_hint<WAVEFactChunk>(WAVEFactChunk::Ignore));
      CHECK(get_hint<WAVEFactChunk>() == WAVEFactChunk::Ignore);

      CHECK(set_hint<WAVEFactChunk>(WAVEFactChunk::IgnoreZero));
      CHECK(get_hint<WAVEFactChunk>() == WAVEFactChunk::IgnoreZero);

      CHECK(set_hint<WAVEFactChunk>(WAVEFactChunk::Strict));
      CHECK(get_hint<WAVEFactChunk>() == WAVEFactChunk::Strict);
    });
  };

  SECTION("WindowsDisableThreadNaming")
  {
    test_bool_hint<WindowsDisableThreadNaming>();
  };

  SECTION("WinD3DCompiler")
  {
    test_hint<WinD3DCompiler>([] {
      CHECK(set_hint<WinD3DCompiler>(WinD3DCompiler::None));
      CHECK(get_hint<WinD3DCompiler>() == WinD3DCompiler::None);

      CHECK(set_hint<WinD3DCompiler>(WinD3DCompiler::D3DCompiler46));
      CHECK(get_hint<WinD3DCompiler>() == WinD3DCompiler::D3DCompiler46);

      CHECK(set_hint<WinD3DCompiler>(WinD3DCompiler::D3DCompiler43));
      CHECK(get_hint<WinD3DCompiler>() == WinD3DCompiler::D3DCompiler43);
    });
  }

  SECTION("WindowsEnableMessageLoop")
  {
    test_bool_hint<WindowsEnableMessageLoop>();
  };

  SECTION("WindowsNoCloseOnAltF4") { test_bool_hint<WindowsNoCloseOnAltF4>(); };

  SECTION("WindowFrameUsableWhileCursorHidden")
  {
    test_bool_hint<WindowFrameUsableWhileCursorHidden>();
  };

  SECTION("WinRTPrivacyPolicyLabel")
  {
    test_hint<WinRTPrivacyPolicyLabel>([] {
      const CZString str = "Hello this is GDPR speaking";
      set_hint<WinRTPrivacyPolicyLabel>(str);
      CHECK_THAT(get_hint<WinRTPrivacyPolicyLabel>().value(),
                 Catch::Equals(str));
    });
  }

  SECTION("WinRTPrivacyPolicyURL")
  {
    test_hint<WinRTPrivacyPolicyURL>([] {
      const CZString str = "Hello this is GDPR URL speaking";
      set_hint<WinRTPrivacyPolicyURL>(str);
      CHECK_THAT(get_hint<WinRTPrivacyPolicyURL>().value(), Catch::Equals(str));
    });
  }

  SECTION("MouseTouchEvents") { test_bool_hint<MouseTouchEvents>(); };

  SECTION("RenderBatching") { test_bool_hint<RenderBatching>(); };

  SECTION("ReturnKeyHidesIME") { test_bool_hint<ReturnKeyHidesIME>(); };

  SECTION("TouchMouseEvents") { test_bool_hint<TouchMouseEvents>(); };

  SECTION("TVRemoteAsJoystick") { test_bool_hint<TVRemoteAsJoystick>(); };

  SECTION("XinputEnabled") { test_bool_hint<XinputEnabled>(); };

  SECTION("XinputUseOldJoystickMapping")
  {
    test_bool_hint<XinputUseOldJoystickMapping>();
  };

  SECTION("RenderDriver")
  {
    test_hint<RenderDriver>([] {
      CHECK(set_hint<RenderDriver>(RenderDriver::OpenGL));
      CHECK(get_hint<RenderDriver>().value() == RenderDriver::OpenGL);

      CHECK(set_hint<RenderDriver>(RenderDriver::OpenGLES));
      CHECK(get_hint<RenderDriver>().value() == RenderDriver::OpenGLES);

      CHECK(set_hint<RenderDriver>(RenderDriver::OpenGLES2));
      CHECK(get_hint<RenderDriver>().value() == RenderDriver::OpenGLES2);

      CHECK(set_hint<RenderDriver>(RenderDriver::Metal));
      CHECK(get_hint<RenderDriver>().value() == RenderDriver::Metal);

      CHECK(set_hint<RenderDriver>(RenderDriver::Direct3D));
      CHECK(get_hint<RenderDriver>().value() == RenderDriver::Direct3D);

      CHECK(set_hint<RenderDriver>(RenderDriver::Software));
      CHECK(get_hint<RenderDriver>().value() == RenderDriver::Software);
    });

    set_hint<RenderDriver>(RenderDriver::OpenGL);
  }
}

TEST_CASE("add_callback", "[Hints]")
{
  set_hint<RenderDriver>(RenderDriver::Software);

  int data = 7;
  auto handle = add_callback<RenderDriver>(
      [](void* data, CZString hint, CZString oldVal, CZString newVal) {
        static bool first = true;
        if (first) {
          first = false;
        } else {
          const auto ptr = reinterpret_cast<int*>(data);
          CHECK(*ptr == 7);
          CHECK_THAT(SDL_HINT_RENDER_DRIVER, Catch::Equals(hint));
          CHECK_THAT("software", Catch::Equals(oldVal));
          CHECK_THAT("opengl", Catch::Equals(newVal));
        }
      },
      &data);

  set_hint<RenderDriver, Prio::Override>(RenderDriver::Software);

  handle.disconnect();

  set_hint<RenderDriver, Prio::Override>(RenderDriver::OpenGL);
}

TEST_CASE("clear_all", "[Hints]")
{
  CHECK_NOTHROW(clear_all());
}

TEST_CASE("user_data", "[hint::Callback]")
{
  int i = 123;
  Callback<RenderDriver> callback{[](void*, CZString, CZString, CZString) {},
                                  &i};
  CHECK(callback.user_data() == &i);
}