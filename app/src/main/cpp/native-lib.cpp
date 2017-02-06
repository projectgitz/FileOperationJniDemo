#include <jni.h>
#include <string>

extern "C"
jstring
Java_com_chetan_fileoperationjnidemo_MainActivity_getTextFromFile(
        JNIEnv *env,
        jobject, jstring path) {
    const char *pathString = env->GetStringUTFChars(path, JNI_FALSE);
    std::string myStr ("");
    FILE *fp = fopen(pathString, "r");
    if (fp != NULL) {
        while (1) {
            char c = fgetc(fp);
            if (feof(fp)) {
                break;
            }
            myStr+=c;
        }
        fclose(fp);
        env->ReleaseStringUTFChars(path, pathString);
        return env->NewStringUTF(myStr.c_str());
    } else {
        fclose(fp);
        env->ReleaseStringUTFChars(path, pathString);
        return env->NewStringUTF("Error opening file!");
    }
}

extern "C"
void
Java_com_chetan_fileoperationjnidemo_MainActivity_saveTextToFile(
        JNIEnv *env,
        jobject, jstring path, jstring message) {
    const char *pathString = env->GetStringUTFChars(path, JNI_FALSE);
    const char *messageString = env->GetStringUTFChars(message, JNI_FALSE);
    FILE *file = fopen(pathString, "w+");
    if (file != NULL) {
        fputs(messageString, file);
        fflush(file);
        fclose(file);
    }
    env->ReleaseStringUTFChars(path, pathString);
    env->ReleaseStringUTFChars(message, messageString);
}
