class Elevator {

    constructor(id, startFloor) {
        this.id = id;
        this.current_floor = startFloor;
        this.moving = false;
    }

    display_floor() {

        document.getElementById(
            `currentFloor${this.id}`
        ).textContent = this.current_floor;
    }

    async move(targetFloor) {

        // 正在移動就不接受新的移動指令
        if (this.moving) {
            return;
        }

        // 限制 1 ~ 10 樓
        if (targetFloor < 1 || targetFloor > 10) {
            return;
        }

        // 已經在目標樓層
        if (this.current_floor === targetFloor) {
            return;
        }

        this.moving = true;

        this.setStatus("Moving...");

        while (this.current_floor !== targetFloor) {

            if (this.current_floor < targetFloor) {
                this.current_floor++;
            }
            else {
                this.current_floor--;
            }

            this.display_floor();

            // 每層移動 1 秒
            await new Promise(resolve => {
                setTimeout(resolve, 1000);
            });
        }

        this.moving = false;

        this.setStatus("Arrived");
    }


    setStatus(status) {

        document.getElementById(
            `status${this.id}`
        ).textContent = status;
    }
}


// 建立兩台電梯
const elevator1 = new Elevator(1, 1);
const elevator2 = new Elevator(2, 10);


// Elevator 1
document.getElementById("goButton1")
    .addEventListener("click", () => {

        const target = Number(
            document.getElementById("targetFloor1").value
        );

        elevator1.move(target);
    });


// Elevator 2
document.getElementById("goButton2")
    .addEventListener("click", () => {

        const target = Number(
            document.getElementById("targetFloor2").value
        );

        elevator2.move(target);
    });


// 初始顯示
elevator1.display_floor();
elevator2.display_floor();