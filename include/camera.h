#ifndef CAMERA_H
#define CAMERA_H

#include <cglm/types.h>
#include <cglm/vec3.h>
#include <cglm/cam.h>

#define NEAR_PLANE_DIST 0.1f
#define FAR_PLANE_DIST 200.0f

typedef enum{
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT
} CameraMovement;

typedef struct{
    vec3 position;
    vec3 front;
    vec3 up;
    vec3 right;
    vec3 world_up;
    float yaw;
    float pitch;
    float movement_speed;
    float mouse_sensitivity;
    float zoom;
    float aspect_ratio;
    float near_plane_dist;
    float far_plane_dist;
} Camera;

/*
    Create a camera at position {pos_x, pos_y, pos_z}
    with world_up vector {up_x, up_y, up_z}
    and yaw and pitch. 
    Other values of camera will use default values
    Stores resulting camera in result
*/
void camera_create(float pos_x, float pos_y, float pos_z, float up_x, float up_y, float up_z, float yaw, float pitch, float aspect_ratio, Camera* result);

/*
    Gets the projection matrix for a perspective view from this camera and stores it in result
*/
void camera_get_perspective(Camera* cam, mat4 result);

/*
    Gets the view matrix of the camera in it's current state and stores it in result
*/
void camera_get_view_matrix(Camera* cam, mat4 result);

/*
    Handles updates of camera position caused by keyboard input
*/
void camera_process_keyboard_movement(Camera* cam, CameraMovement movement, float delta_time);

/*
    Handles updates of camera pitch and yaw caused by mouse input
*/
void camera_process_mouse_movement(Camera* cam, float x_offset, float y_offset, unsigned char constrain_pitch);

/*
    Handles updates to camera zoom caused by scrolling the mouse wheel
*/
void camera_process_mouse_scroll(Camera* cam, float y_offset);

#endif
