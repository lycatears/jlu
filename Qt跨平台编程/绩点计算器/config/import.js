(function () {
    let table = document.getElementById("pinnedtableqb-index-table");
    let data = [];
    for (let i = 0; i < table.rows.length; i++) {
        let rowObject = {};
        let row = table.rows[i];

        let score = row.cells[1].innerText;
        switch (score) {
            case "优秀":
                score = "95";
                break;
            case "良好":
                score = "85";
                break;
            case "中等":
                score = "75";
                break;
            case "及格":
                score = "65";
                break;
            case "不及格":
                score = "0";
                break;
        }
        rowObject["score"] = score;
        rowObject["gpa"] = row.cells[13].children[0].innerHTML;
        rowObject["credit"] = row.cells[8].children[0].innerHTML;
        rowObject["subject-name"] = row.cells[3].children[0].innerHTML;

        data.push(rowObject);
    }
    console.log(JSON.stringify(data));
    return JSON.stringify(data);
})();