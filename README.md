# Retono — public files

Public files for **Retono: Karaoke & Chords**, an Android app that changes the key and tempo of songs, removes vocals or instruments and shows chords. All processing happens on the phone.

- [Privacy policy](PRIVACY.md)
- [Support & feedback](../../issues) — questions, bug reports and ideas are welcome (English or Russian).

## What is here

| Folder | Contents |
|---|---|
| `models/` | Vocal/instrument separation models the app downloads on first use (2, 4 and 5 tracks). |
| `lame-jni/` | The exact LAME MP3 encoder source code built into the app, with the JNI wrapper and build script. |
| `play/` | Short screen recordings used for the Google Play foreground-service declaration. |

## Licenses

- **Separation models** — converted to ONNX from [Spleeter](https://github.com/deezer/spleeter) by Deezer Research (MIT License). The 2-track model comes from the [sherpa-onnx](https://github.com/k2-fsa/sherpa-onnx) export (Apache License 2.0); the 4- and 5-track models were converted from the original Spleeter checkpoints. The 5-track files are split into parts under 20 MB for CDN delivery and joined by the app.
- **LAME** — GNU Lesser General Public License 2.0, see `lame-jni/lame/COPYING`. You may rebuild `libmp3lame` from `lame-jni/` with the Android NDK (`CMakeLists.txt`) and replace the library in the app.
