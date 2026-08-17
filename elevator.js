class Elevator {
    constructor(id, start_floor) {
        this.id = id;
        this.current_floor = start_floor;
        this.moving = false;
        this.create_UI();
        this.display_floor();
        this.setStatus("Idle");
    }

    async move(targetFloor) {

        if (this.moving) {
            return;
        }
        if (targetFloor < 1 || targetFloor > 10) {
            return;
        }
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

            await new Promise(resolve => {
                setTimeout(resolve, 1000);
            });
        }

        this.moving = false;

        this.setStatus("Arrived");
    }

    setStatus(status) {
        this.statusElement.textContent = status;
    }

    display_floor() {
        this.curr_input.value = this.current_floor;
    }

    create_UI() {
        // div
        this.element = document.createElement("div");
        this.element.className = "elevator";

        // title id
        const title = document.createElement("h2");
        title.textContent = `Elevator ${this.id}`;

        // stauts
        const status_text = document.createElement("p");
        status_text.textContent = "Status: ";

        this.statusElement = document.createElement("span");
        status_text.appendChild(this.statusElement);

        // input current floor
        const curr_floor = document.createElement("p");
        curr_floor.textContent = "Current Floor: ";

        this.curr_input = document.createElement("input");
        this.curr_input.type = "number";
        this.curr_input.min = 1;
        this.curr_input.max = 10;
        this.curr_input.value = this.current_floor;

        curr_floor.appendChild(this.curr_input);
        this.curr_input.addEventListener("change", () => {
            const floor = Number(this.curr_input.value);
            if (floor >= 1 && floor <= 10) {
                this.current_floor = floor;
            }
        });

        // input target floor
        const target_floor = document.createElement("p");
        target_floor.textContent = "Target Floor: ";

        this.target_input = document.createElement("input");
        this.target_input.type = "number";
        this.target_input.min = 1;
        this.target_input.max = 10;

        target_floor.appendChild(this.target_input);

        // buttom
        this.button = document.createElement("button");
        this.button.textContent = "Go";
        this.button.addEventListener("click", () => {
            const targetFloor = Number(this.target_input.value);
            this.move(targetFloor);
        });
        
        this.element.appendChild(title);
        this.element.appendChild(status_text);
        this.element.appendChild(curr_floor);
        this.element.appendChild(target_floor);
        this.element.appendChild(this.button);

        document
            .getElementById("elevators")
            .appendChild(this.element);
    }
}

const elevator1 = new Elevator(1, Math.floor(Math.random() * 10) + 1);
const elevator2 = new Elevator(2, Math.floor(Math.random() * 10) + 1);