import cv2
import numpy as np

cap = cv2.VideoCapture("IMG.MOV")

while(True) :
    ref,frame = cap.read()
    roi = frame[:1080,:1920]

    GrayScale = cv2.cvtColor(frame,cv2.COLOR_BGR2GRAY) #เปลี่ยนภาพเป็นแบบ GrayScale เป้นการขยายภาพ(Dilation)
    GrayScale_blur = cv2.GaussianBlur(GrayScale,(15,15),0) #ทำให้ภาพเบลอ
    threshold = cv2.adaptiveThreshold(GrayScale_blur,255,cv2.ADAPTIVE_THRESH_GAUSSIAN_C,cv2.THRESH_BINARY_INV,11,1) #ทำภาพให้เป็น Threshold
    kernel = np.ones((3,3),np.uint8) # unit8 คือ data type
    closing = cv2.morphologyEx(threshold,cv2.MORPH_CLOSE,kernel,iterations = 4) #ทำภาพให้เป็น Closing
    
    result_img = closing.copy()
    contours, hierachy = cv2.findContours(result_img,cv2.RETR_EXTERNAL,cv2.CHAIN_APPROX_SIMPLE) #RETR_EXTERNAL คือ หาขอบนอกสุดของเหรียญ, CHAIN_APPROX_SIMPLE คือทำให้กระชับเข้ากับสัดส่วนของเหรียญ
    counter = 0
    for cnt in contours:
        area = cv2.contourArea(cnt)
        if area<5000 or area>35000:
            continue
        ellipse = cv2.fitEllipse(cnt)
        cv2.ellipse(roi,ellipse,(0,0,255),2)
        circles = cv2.HoughCircles(GrayScale, cv2.HOUGH_GRADIENT, 1, 100, param1=100, param2=90, minRadius=0, maxRadius=200)
        circles = np.round(circles[0, :]).astype("int")
        for (x, y, r) in circles:
            cv2.rectangle(roi, (x - 2, y - 2), (x + 2, y + 2), (0,255,0), -1)
        counter += 1

    cv2.putText(roi,str(counter),(10,100),cv2.FONT_HERSHEY_SIMPLEX,4,(0,0,0),2,cv2.LINE_AA)
    cv2.imshow("Show",roi)
    if cv2.waitKey(1) & 0xFF==ord('q'):
        break

cap.release()
cv2.destroyAllWindows()