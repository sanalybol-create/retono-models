// JNI bridge to the LAME MP3 encoder.
#include <jni.h>
#include <stdint.h>
#include <stdlib.h>
#include "lame.h"

JNIEXPORT jlong JNICALL
Java_com_minusovka_app_audio_Mp3Encoder_nativeInit(JNIEnv *env, jclass cls, jint sampleRate, jint bitrateKbps) {
    lame_global_flags *gf = lame_init();
    if (!gf) return 0;
    lame_set_in_samplerate(gf, sampleRate);
    lame_set_out_samplerate(gf, sampleRate);
    lame_set_num_channels(gf, 2);
    lame_set_mode(gf, JOINT_STEREO);
    lame_set_VBR(gf, vbr_off);
    lame_set_brate(gf, bitrateKbps);
    lame_set_quality(gf, 2);
    lame_set_bWriteVbrTag(gf, 0);
    if (lame_init_params(gf) < 0) {
        lame_close(gf);
        return 0;
    }
    return (jlong) (intptr_t) gf;
}

JNIEXPORT jint JNICALL
Java_com_minusovka_app_audio_Mp3Encoder_nativeEncode(JNIEnv *env, jclass cls, jlong handle,
                                                     jshortArray pcm, jint frames, jbyteArray out) {
    lame_global_flags *gf = (lame_global_flags *) (intptr_t) handle;
    jshort *in = (*env)->GetShortArrayElements(env, pcm, NULL);
    jbyte *o = (*env)->GetByteArrayElements(env, out, NULL);
    jsize outLen = (*env)->GetArrayLength(env, out);
    int n = lame_encode_buffer_interleaved(gf, in, frames, (unsigned char *) o, outLen);
    (*env)->ReleaseShortArrayElements(env, pcm, in, JNI_ABORT);
    (*env)->ReleaseByteArrayElements(env, out, o, 0);
    return n;
}

JNIEXPORT jint JNICALL
Java_com_minusovka_app_audio_Mp3Encoder_nativeFlush(JNIEnv *env, jclass cls, jlong handle, jbyteArray out) {
    lame_global_flags *gf = (lame_global_flags *) (intptr_t) handle;
    jbyte *o = (*env)->GetByteArrayElements(env, out, NULL);
    jsize outLen = (*env)->GetArrayLength(env, out);
    int n = lame_encode_flush(gf, (unsigned char *) o, outLen);
    (*env)->ReleaseByteArrayElements(env, out, o, 0);
    return n;
}

JNIEXPORT void JNICALL
Java_com_minusovka_app_audio_Mp3Encoder_nativeClose(JNIEnv *env, jclass cls, jlong handle) {
    lame_global_flags *gf = (lame_global_flags *) (intptr_t) handle;
    if (gf) lame_close(gf);
}
