/*
 * Problem: Design Video Sharing Platform
 * Difficulty: Hard
 * Tags: array, string, tree, hash, stack
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(h) for recursion stack where h is height
 */




typedef struct {
    
} VideoSharingPlatform;


VideoSharingPlatform* videoSharingPlatformCreate() {
    
}

int videoSharingPlatformUpload(VideoSharingPlatform* obj, char* video) {
    
}

void videoSharingPlatformRemove(VideoSharingPlatform* obj, int videoId) {
    
}

char* videoSharingPlatformWatch(VideoSharingPlatform* obj, int videoId, int startMinute, int endMinute) {
    
}

void videoSharingPlatformLike(VideoSharingPlatform* obj, int videoId) {
    
}

void videoSharingPlatformDislike(VideoSharingPlatform* obj, int videoId) {
    
}

int* videoSharingPlatformGetLikesAndDislikes(VideoSharingPlatform* obj, int videoId, int* retSize) {
    
}

int videoSharingPlatformGetViews(VideoSharingPlatform* obj, int videoId) {
    
}

void videoSharingPlatformFree(VideoSharingPlatform* obj) {
    
}

/**
 * Your VideoSharingPlatform struct will be instantiated and called as such:
 * VideoSharingPlatform* obj = videoSharingPlatformCreate();
 * int param_1 = videoSharingPlatformUpload(obj, video);
 
 * videoSharingPlatformRemove(obj, videoId);
 
 * char* param_3 = videoSharingPlatformWatch(obj, videoId, startMinute, endMinute);
 
 * videoSharingPlatformLike(obj, videoId);
 
 * videoSharingPlatformDislike(obj, videoId);
 
 * int* param_6 = videoSharingPlatformGetLikesAndDislikes(obj, videoId, retSize);
 
 * int param_7 = videoSharingPlatformGetViews(obj, videoId);
 
 * videoSharingPlatformFree(obj);
*/