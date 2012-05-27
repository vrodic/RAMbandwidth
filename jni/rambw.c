/* Used code from MBW, afaik it is LGPL (from debian copyright files)
 *
 * https://github.com/raas/mbw
 * 2006, 2012 Andras.Horvath atnospam gmail.com
 *
 * Anyway, the code is quite trivial, and MBW was reused to be able to compare easily with Ubuntu PC
 * (apt-get install mbw)
 *
 *
 */
#include <string.h>
#include <sys/time.h>
#include <jni.h>
#include <android/log.h>




#define  LOG_TAG    "libmbw"
#define  LOGI(...)  __android_log_print(ANDROID_LOG_INFO,LOG_TAG,__VA_ARGS__)
#define  LOGW(...)  __android_log_print(ANDROID_LOG_WARN,LOG_TAG,__VA_ARGS__)
#define  LOGE(...)  __android_log_print(ANDROID_LOG_ERROR,LOG_TAG,__VA_ARGS__)

long *make_array(unsigned long long asize) {
	unsigned long long t;
	unsigned int long_size = sizeof(long);
	long *a;

	a = calloc(asize, long_size);

	if (NULL == a) {
		return NULL;

	}

	/* make sure both arrays are allocated, fill with pattern */
	for (t = 0; t < asize; t++) {
		a[t] = 0xaa;
	}
	return a;
}

double worker(unsigned long long asize, long *a, long *b) {
	unsigned long long t;
	struct timeval starttime, endtime;
	double te;
	unsigned int long_size = sizeof(long);
	/* array size in bytes */
	unsigned long long array_bytes = asize * long_size;

	gettimeofday(&starttime, NULL);
	for (t = 0; t < asize; t++) {
		b[t] = a[t];
	}
	gettimeofday(&endtime, NULL);

	te = ((double) (endtime.tv_sec * 1000000 - starttime.tv_sec * 1000000
			+ endtime.tv_usec - starttime.tv_usec)) / 1000000;

	return te;
}

void printout(double te, double mt)
{

    LOGI("Elapsed: %.5f\t", te);
    LOGI("MiB: %.5f\t", mt);
    LOGI("Copy: %.3f MiB/s\n", mt/te);
    return;
}

double test(double mt, int nr_loops) {
	unsigned int long_size = 0;
	double te, te_sum; /* time elapsed */
	unsigned long long asize = 0; /* array size (elements in array) */
	int i;
	long *a, *b; /* the two arrays to be copied from/to */

	/* how many runs to average? */

	long_size = sizeof(long); /* the size of long on this platform */
	asize = 1024 * 1024 / long_size * mt;

	a = make_array(asize);
	if (a == NULL)
	{
		return 0;
	}

	b = make_array(asize);
	if (b == NULL)
	{
		return 0;
	}
	LOGI("initialized arrays");
	worker(asize, a, b); /* one warmup run */
	te_sum = 0;

	for (i = 0; i < nr_loops; i++) {
		te = worker(asize, a, b);
		te_sum += te;
		printout(te, mt);
	}
	printout(te_sum/nr_loops, mt);
	LOGI("finished tests");
	free(a);
	free(b);
	return mt / (te_sum / nr_loops);
}



jdouble Java_org_vrodic_rambandwidth_RAMbandwidth_testMBW(JNIEnv* env,
		jobject thiz, jdouble mt, jint nr_loops)
{
	return (jdouble)(test((double)mt, (int)nr_loops));
}

