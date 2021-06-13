#include <jni.h>
#include <string>

#include <android/native_window_jni.h>

extern "C" {
JNIEXPORT void JNICALL Java_java_com_example_learning_1camera2_MainActivity_stopPreview(JNIEnv *env,
                                                                                    jobject);
JNIEXPORT void JNICALL Java_java_com_example_learning_1camera2_MainActivity_startPreview(JNIEnv *env,
                                                                                     jobject,
                                                                                     jobject surface);
}

extern "C" {
JNIEXPORT void JNICALL Java_java_com_example_learning_1camera2_MainActivity_startPreview(JNIEnv *env,
                                                                                     jobject,
                                                                                     jobject surface) {
    ANativeWindow *theNativeWindow = ANativeWindow_fromSurface(env, surface);

}

JNIEXPORT void JNICALL Java_java_com_example_learning_1camera2_MainActivity_stopPreview(JNIEnv *env,
                                                                                    jobject) {
}
}