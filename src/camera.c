#include <camera.h>

const float YAW = -90.0f;
const float PITCH = 0.0f;
const float SPEED = 100.0f;
const float SENSITIVITY = 0.1f;
const float ZOOM = 45.0f;

void update_camera_vectors(Camera* cam){
    // Calculate new front vector
    cam->front[0] = cos(glm_rad(cam->yaw)) * cos(glm_rad(cam->pitch));
    cam->front[1] = sin(glm_rad(cam->pitch));
    cam->front[2] = sin(glm_rad(cam->yaw)) * cos(glm_rad(cam->pitch));
    glm_vec3_normalize(cam->front);

    // Use new front vector to calculate right and up vectors
    glm_vec3_cross(cam->front, cam->world_up, cam->right);
    glm_vec3_normalize(cam->right);

    glm_vec3_cross(cam->right, cam->front, cam->up);
    glm_vec3_normalize(cam->up);
}

Camera camera_create(float pos_x, float pos_y, float pos_z, float up_x, float up_y, float up_z, float yaw, float pitch, float aspect_ratio){
    Camera camera = {
        .position = {pos_x, pos_y, pos_z},
        .world_up = {up_x, up_y, up_z},
        .front = {0.0f, 0.0f, -1.0f},
        .movement_speed = SPEED,
        .mouse_sensitivity = SENSITIVITY,
        .zoom = ZOOM,
        .yaw = yaw,
        .pitch = pitch,
        .aspect_ratio = aspect_ratio,
        .near_plane_dist = NEAR_PLANE_DIST,
        .far_plane_dist = FAR_PLANE_DIST
    };
    update_camera_vectors(&camera); // Make sure vectors are up to date
    return camera;
}

void camera_get_view_matrix(Camera* cam, mat4 result){
    vec3 sum; // Temp vector for storing sum of position and up vector
    
    // Add position and up vector
    glm_vec3_add(cam->position, cam->front, sum);

    // Calculate view matrix and store in result
    glm_lookat(cam->position, sum, cam->up, result);
}

void camera_get_perspective(Camera* cam, mat4 result){
    glm_perspective(glm_rad(cam->zoom), cam->aspect_ratio, cam->near_plane_dist, cam->far_plane_dist, result);
}

void camera_process_keyboard_movement(Camera* cam, CameraMovement movement, float delta_time){
    // Calculate velocity
    float velocity = cam->movement_speed * delta_time;

    // Update position based on direction and speed
    if(movement == FORWARD)
        glm_vec3_muladds(cam->front,  velocity, cam->position);
    if(movement == BACKWARD)
        glm_vec3_muladds(cam->front, -velocity, cam->position);
    if(movement == LEFT)
        glm_vec3_muladds(cam->right, -velocity, cam->position);
    if(movement == RIGHT)
        glm_vec3_muladds(cam->right,  velocity, cam->position);
}

void camera_process_mouse_movement(Camera* cam, float x_offset, float y_offset, unsigned char constrain_pitch){
    // Scale offsets by sensitivity
    x_offset *= cam->mouse_sensitivity;
    y_offset *= cam->mouse_sensitivity;

    // Add offsets to pitch and yaw
    cam->yaw += x_offset;
    cam->pitch += y_offset;

    // Check pitch constraint
    if (constrain_pitch) {
        if(cam->pitch > 89.0f)
            cam->pitch = 89.0f;
        if(cam->pitch < -89.0f)
            cam->pitch = -89.0f;
    }

    // Update camera vectors
    update_camera_vectors(cam);
}

void camera_process_mouse_scroll(Camera* cam, float y_offset){
    // Add offset to zoom
    cam->zoom -= y_offset;

    // Check zoom constraint
    if(cam->zoom < 1.0f)
        cam->zoom = 1.0f;
    if(cam->zoom > 45.0f)
        cam->zoom = 45.0f;
}
