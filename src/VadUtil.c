#include <jni.h>
#include <stdio.h>
#include <fvad.h>
#include "VadUtil.h"

JNIEXPORT jlong JNICALL Java_VadUtil_create(JNIEnv * env, jclass thisClass) {
    Fvad *fvad = fvad_new();
    return (long) fvad;
}

JNIEXPORT void JNICALL Java_VadUtil_free(JNIEnv * env, jclass thisClass, jlong ptr) {
    Fvad *fvad = (Fvad *) ptr;
    fvad_free(fvad);
}

JNIEXPORT void JNICALL Java_VadUtil_reset(JNIEnv * env, jclass thisClass, jlong ptr) {
    Fvad *fvad = (Fvad *) ptr;
    fvad_reset(fvad);
}

JNIEXPORT jint JNICALL Java_VadUtil_setMode(JNIEnv * env, jclass thisClass, jlong ptr, jint mode) {
    Fvad *fvad = (Fvad *) ptr;
    return fvad_set_mode(fvad, mode);
}

JNIEXPORT jint JNICALL Java_VadUtil_setSampleRate(JNIEnv * env, jclass thisClass, jlong ptr, jint sampleRate) {
    Fvad *fvad = (Fvad *) ptr;
    return fvad_set_sample_rate(fvad, sampleRate);
}

JNIEXPORT jint JNICALL Java_VadUtil_process(JNIEnv * env, jclass thisClass, jlong ptr, jshortArray frames) {
    Fvad *fvad = (Fvad *) ptr;
    jsize size = (* env)->GetArrayLength(env, frames);
    jshort *shortArray = (* env)->GetShortArrayElements(env, frames, NULL);
    int state = fvad_process(fvad, shortArray, size);
    (*env)->ReleaseShortArrayElements(env, frames, shortArray, 0);
    return state;
}