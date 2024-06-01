#ifndef YOLO_INFERENCE_H_
#define YOLO_INFERENCE_H_

#include <iostream>
#include <string>
#include <vector>

#include <opencv2/dnn.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <openvino/openvino.hpp>

namespace yolo {
struct Detection {
	short class_id;
	float confidence;
	cv::Rect box;
};

class Inference {
 public:
	Inference() {}
	Inference(const std::string &model_path);

	std::vector<Detection> RunInference(const cv::Mat &frame);

 private:
	void InitialModel(const std::string &model_path);
	void Preprocessing(const cv::Mat &frame);
	void PostProcessing();
	cv::Rect GetBoundingBox(const cv::Rect &src);

	cv::Mat resized_frame_;
	cv::Point2f factor_;
	cv::Size2f model_input_shape_;
	cv::Size model_output_shape_;

	ov::Tensor input_tensor_;
	ov::InferRequest inference_request_;
	ov::CompiledModel compiled_model_;

	std::vector<Detection> detections_;

	float model_confidence_threshold_;
};
} // namespace yolo

#endif // YOLO_INFERENCE_H_
