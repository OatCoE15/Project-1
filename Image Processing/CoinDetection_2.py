import cv2
import numpy as np

image = cv2.imread("IMG_0126.jpg",0)
output = cv2.imread("IMG_0126.jpg",1)
blurred = cv2.GaussianBlur(image,(11,11),0)
circles = cv2.HoughCircles(blurred, cv2.HOUGH_GRADIENT, 1, 100, param1=100, param2=90, minRadius=0, maxRadius=200)

if circles is not None:
    # If there are some detections, convert radius and x,y(center) coordinates to integer
    circles = np.round(circles[0, :]).astype("int")
    counter = 0
    for (x, y, r) in circles:
        # Draw the circle in the output image
        cv2.circle(output, (x, y), r, (0,0,255), 3)
        # Draw a rectangle(center) in the output image
        cv2.circle(output, (x, y), 2, (0,255,0), 2)
        #cv2.rectangle(output, (x - 2, y - 2), (x + 2, y + 2), (0,255,0), -1)
        radians = '%.2f'%((r*0.026458333333333)/0.1)
        counter += 1
        print(radians, 'mm')

cv2.putText(output,str(counter),(10,150),cv2.FONT_HERSHEY_SIMPLEX,6,(0,0,0),4,cv2.LINE_AA)        
cv2.imshow("Detections",output)
cv2.waitKey()

