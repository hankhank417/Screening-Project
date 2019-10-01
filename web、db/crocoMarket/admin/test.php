<center>
    <form action="/list" enctype="multipart/form-data">
        <img id="preview_img" src="#" width="80%" alt="photo" class="img-thumbnail" style="margin-top:25px; max-height:250px;display:block; margin-right: auto;margin-left: auto;">
        <input type="file" name="imgInput" onchange="readURL(this)" targetID="preview_img" accept="image/*"/>
        <button  type="button" onclick="imgInput.click()" style="width:50%; margin-top: 6px;" class="btn btn-outline-primary">更換圖片</button>
    </form>
</center>
<script>
    function readURL(input){
        alert('測試文字');
        if(input.files && input.files[0]){
            var imageTagID = input.getAttribute("targetID");
            var reader = new FileReader();
            reader.onload = function (e) {
                var img = document.getElementById(imageTagID);
                img.setAttribute("src", e.target.result)
            }
            reader.readAsDataURL(input.files[0]);
        }
    }
</script>