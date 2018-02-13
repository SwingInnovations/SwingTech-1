--Initialize stuff here
function start(self)
    print("Initializing Script");
    AddEvent(self, "onCollision");
end

function update(self)

end

-- On Collision Flag
function onCollision(self, other)
    if other:getName() == "Plane" then
--        Remove(self)
        print("Collided");
    end
end