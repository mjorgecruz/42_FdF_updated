import cv2
import os

# Replace 'your_video_file.mp4' with the path to your video file
video_path = 'test.mp4'

# Create a VideoCapture object
cap = cv2.VideoCapture(video_path)

# Check if the video file is opened successfully
if not cap.isOpened():
    print("Error: Could not open video file.")
    exit()

# Create a directory to store the frames
output_directory = 'frames'
os.makedirs(output_directory, exist_ok=True)

# Loop to read frames from the video
frame_count = 0
while True:
    # Read a frame from the video
    ret, frame = cap.read()

    # Check if the frame is read successfully
    if not ret:
        print("End of video.")
        break

    # Save the frame as an image file
    frame_filename = os.path.join(output_directory, f'frame_{frame_count:04d}.png')
    cv2.imwrite(frame_filename, frame)

    frame_count += 1

# Release the VideoCapture object
cap.release()

print(f"{frame_count} frames saved in '{output_directory}'.")