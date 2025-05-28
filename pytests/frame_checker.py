import cv2
import numpy as np

class VideoColorChecker:
    def __init__(self, video_path, frame_number):
        self._frame = VideoColorChecker.extract_frame(video_path, frame_number)

    def isOpen(self):
        if '_frame' in self.__dict__:
            return True
        else:
            return False

    def RelativeCheckAt(self, position, expected_color, tolerance):
        return VideoColorChecker.check_color_at_position(self._frame, expected_color, 
                                                         (position[0]*self._frame.shape[1], position[1]*self._frame.shape[0]), 
                                                         tolerance)

    def CheckAt(self, position, expected_color, tolerance):
        return VideoColorChecker.check_color_at_position(self._frame, expected_color, position, tolerance)

    @staticmethod
    def color_distance(color1, color2):
        # Calculate the Euclidean distance between two colors
        return np.linalg.norm(np.array(color1) - np.array(color2))

    @staticmethod
    def check_color_at_position(frame, target_color, position, tolerance):
        # Get the color at the specified position
        # Note: OpenCV uses BGR format by default
        pixel_color = frame[int(position[1]), int(position[0])]  # (x, y) format
        
        # Calculate the distance between the target color and the pixel color
        distance = VideoColorChecker.color_distance(pixel_color, target_color)
        
        # Check if the distance is within the tolerance
        if distance <= tolerance:
            print(f"The color {pixel_color} at position {position} is within the tolerance. Distance: {distance:.2f}")
            return True
        else:
            print(f"The color {pixel_color} at position {position} is not within the tolerance. Distance: {distance:.2f}")
            return False

    @staticmethod
    def extract_frame(video_path, frame_number):
        # Open the video file
        cap = cv2.VideoCapture(video_path)
        # Check if the video was opened successfully
        if not cap.isOpened():
            raise ValueError("Could not open the video file.")
        # Set the frame position
        cap.set(cv2.CAP_PROP_POS_FRAMES, frame_number)
        # Read the frame
        ret, frame = cap.read()
        # Check if the frame was read successfully
        if not ret:
            raise ValueError(f"Could not read frame {frame_number} from the video.")
        # Release the video capture object
        cap.release()
        print("Frame: ", frame.shape)
        frame.resize(960, 1280, 3)
        cv2.imwrite('/tmp/image.png', frame)
        # Convert the frame from BGR (OpenCV default) to RGB (Pillow default)
        frame_rgb = cv2.cvtColor(frame, cv2.COLOR_BGR2RGB)
        return frame_rgb
