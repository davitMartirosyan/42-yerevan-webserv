<?php
// Check if the form is submitted
if ($_SERVER["REQUEST_METHOD"] == "POST" && isset($_FILES["filephp"])) {
    $uploadDir = "data_base/"; // Directory where files will be uploaded
    $uploadedFile = $uploadDir . basename($_FILES["filephp"]["name"]);
    $uploadOk = true; // Variable to check if file upload is successful

    // Check if the file already exists
    // if (file_exists($uploadedFile)) {
    //     echo "Sorry, the file already exists.";
    //     $uploadOk = false;
    // }

    // Check file size (you can adjust the file size limit as needed)
    if ($_FILES["filephp"]["size"] > 5000000) { // 5MB limit in this example
        echo "Sorry, your file is too large.";
        $uploadOk = false;
    }

    // Allow only certain file formats/extensions (you can modify this list)
    // $allowedExtensions = array("jpg", "jpeg", "png", "gif");
    // $fileExtension = strtolower(pathinfo($uploadedFile, PATHINFO_EXTENSION));
    // if (!in_array($fileExtension, $allowedExtensions)) {
    //     echo "Sorry, only JPG, JPEG, PNG, and GIF files are allowed.";
    //     $uploadOk = false;
    // }

    // If file upload checks pass, try to upload the file
    if ($uploadOk) {
        if (move_uploaded_file($_FILES["filephp"]["tmp_name"], $uploadedFile)) {
            echo "The file ". basename($_FILES["filephp"]["name"]). " has been uploaded.";
        } else {
            echo "Sorry, there was an error uploading your file.";
        }
    }
} else {
    echo "No file was uploaded.";
}
?>
